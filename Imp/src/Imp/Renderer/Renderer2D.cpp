#include <ImpPCH.h>
#include "Renderer2D.h"

#include "RenderCommand.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Imp/Renderer/UniformBuffer.h"

namespace Imp
{

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;

		int EntityId;
	};

	struct CircleVertex
	{
		glm::vec3 WorldPosition;
		glm::vec3 LocalPosition;
		glm::vec4 Color;
		float Thickness;
		float Fade;

		int EntityId;
	};

	struct LineVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;

		int EntityId;
	};

	struct TextVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;

		int EntityId;
	};

	struct Renderer2DData
	{
		static constexpr uint32_t MaxQuads = 20000;
		static constexpr uint32_t MaxVertices = MaxQuads * 4;
		static constexpr uint32_t MaxIndices = MaxQuads * 6;
		static constexpr uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> QuadShader;
		Ref<Texture2D> WhiteTexture;

		Ref<VertexArray> CircleVertexArray;
		Ref<VertexBuffer> CircleVertexBuffer;
		Ref<Shader> CircleShader;
		Ref<Texture2D> CircleTexture;

		Ref<VertexArray> LineVertexArray;
		Ref<VertexBuffer> LineVertexBuffer;
		Ref<Shader> LineShader;
		Ref<Texture2D> LineTexture;

		Ref<VertexArray> TextVertexArray;
		Ref<VertexBuffer> TextVertexBuffer;
		Ref<Shader> TextShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		uint32_t CircleIndexCount = 0;
		QuadVertex* CircleVertexBufferBase = nullptr;
		QuadVertex* CircleVertexBufferPtr = nullptr;

		uint32_t LineVertexCount = 0;
		QuadVertex* LineVertexBufferBase = nullptr;
		QuadVertex* LineVertexBufferPtr = nullptr;

		uint32_t TextIndexCount = 0;
		QuadVertex* TextVertexBufferBase = nullptr;
		QuadVertex* TextVertexBufferPtr = nullptr;

		float LineWidth = 2.f;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;

		Ref<Texture2D> FontAtlasTexture;
		glm::vec4 QuadVertexPosition[4];

		Renderer2D::Statistics Stats;

		struct CameraData 
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;
	};

	static Renderer2DData s_Data;


	void Renderer2D::Init()
	{
		RenderCommand::Init();
	}

	void Renderer2D::ShutDown()
	{
		IMP_PROFILE_FUNCTION();
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(Camera const& camera, glm::mat4 const& transform)
	{
		IMP_PROFILE_FUNCTION();

		s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));

		StartBatch();
	}

	void Renderer2D::BeginScene(PerspectiveCamera const& camera)
	{
		IMP_PROFILE_FUNCTION();
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));

		StartBatch();
	}

	void Renderer2D::BeginScene(OrthographicCamera const& camera)
	{
		IMP_PROFILE_FUNCTION();

		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));

		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		IMP_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer2D::StartBatch()
	{
		// resetting all data to start a new batch
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.CircleIndexCount = 0;
		s_Data.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;
		s_Data.LineVertexCount = 0;
		s_Data.LineVertexBufferPtr = s_Data.LineVertexBufferBase;
		s_Data.TextIndexCount = 0;
		s_Data.TextVertexBufferPtr = s_Data.TextVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount)
		{
			//Get the data size of the pushed quad vertices and set this data in the vertex buffer
			uint32_t const dataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferBase));
			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

			//bind texture
			for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
				s_Data.TextureSlots[i]->Bind(i);

			//Bind quad shader and draw the data
			s_Data.QuadShader->Bind();
			RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
			s_Data.Stats.DrawCalls++;
		}

		if (s_Data.CircleIndexCount)
		{
			uint32_t const dataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_Data.CircleVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data.CircleVertexBufferBase));
			s_Data.CircleVertexBuffer->SetData(s_Data.CircleVertexBufferBase, dataSize);

			s_Data.CircleShader->Bind();

			RenderCommand::DrawIndexed(s_Data.CircleVertexArray, s_Data.CircleIndexCount);
			s_Data.Stats.DrawCalls++;
		}

		if (s_Data.LineVertexCount)
		{
			uint32_t const dataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_Data.LineVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data.LineVertexBufferBase));
			s_Data.LineVertexBuffer->SetData(s_Data.LineVertexBufferBase, dataSize);

			s_Data.LineShader->Bind();

			RenderCommand::DrawLines(s_Data.LineVertexArray, s_Data.LineVertexCount);
			s_Data.Stats.DrawCalls++;
		}

		if (s_Data.TextIndexCount)
		{
			uint32_t const dataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_Data.TextVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data.TextVertexBufferBase));
			s_Data.TextVertexBuffer->SetData(s_Data.TextVertexBufferBase, dataSize);

			auto buf = s_Data.TextVertexBufferBase;
			s_Data.FontAtlasTexture->Bind(0);

			s_Data.TextShader->Bind();
			RenderCommand::DrawIndexed(s_Data.TextVertexArray, s_Data.TextIndexCount);
			s_Data.Stats.DrawCalls++;
		}
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::DrawQuad(glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color)
	{
	}

	void Renderer2D::DrawQuad(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color)
	{
	}

	void Renderer2D::DrawQuad(glm::vec2 const& position, glm::vec2 const& size, Ref<Texture2D> const&,
		float tilingFactor, glm::vec4 const& tintColor)
	{
	}

	void Renderer2D::DrawQuad(glm::vec3 const& position, glm::vec2 const& size, Ref<Texture2D> const&,
		float tilingFactor, glm::vec4 const& tintColor)
	{
	}

	void Renderer2D::DrawQuad(glm::mat4 const& transform, glm::vec4 const& color, int entityId)
	{
	}

	void Renderer2D::DrawQuad(glm::mat4 const& transform, Ref<Texture2D> const& texture, float tilingFactor,
		glm::vec4 const& tintColor, int entityId)
	{
	}

	void Renderer2D::DrawRotatedQuad(glm::vec2 const& position, glm::vec2 const& size, float rotation,
		glm::vec4 const& color)
	{
	}

	void Renderer2D::DrawRotatedQuad(glm::vec3 const& position, glm::vec2 const& size, float rotation,
		glm::vec4 const& color)
	{
	}

	void Renderer2D::DrawRotatedQuad(glm::vec2 const& position, glm::vec2 const& size, float rotation,
		Ref<Texture2D> const& texture, float tilingFactor, glm::vec4 const& tintColor)
	{
	}

	void Renderer2D::DrawRotatedQuad(glm::vec3 const& position, glm::vec2 const& size, float rotation,
		Ref<Texture2D> const& texture, float tilingFactor, glm::vec4 const& tintColor)
	{
	}

	void Renderer2D::DrawCircle(glm::mat4 const& transform, glm::vec4 const& color, float radius, int entityId)
	{
	}

	void Renderer2D::DrawLine(glm::vec3 const& p0, glm::vec3 const& p1, glm::vec4 const& color, int entityId)
	{
	}

	void Renderer2D::DrawRect(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color, int entityId)
	{
	}

	void Renderer2D::DrawRect(glm::mat4 const& transform, glm::vec4 const& color, int entityId)
	{
	}

	void Renderer2D::DrawSprite(glm::mat4 const& transform, SpriteRendererComponent& source, int entityId)
	{
	}

	void Renderer2D::DrawString(std::string const& string, Ref<FontTexture> font, glm::mat4 const& tranaform,
		TextParams const& textParams, int entityId)
	{
	}

	void Renderer2D::DrawString(std::string const& string, glm::mat4 const& transform, TextComponent const& component,
		int entityId)
	{
	}

	float Renderer2D::GetLineWidth()
	{
	}

	void Renderer2D::SetLineWidth(float width)
	{
	}

	void Renderer2D::ResetStats()
	{
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
	}


	//void Renderer2D::EndScene()
	//{
	//}

	//void Renderer2D::DrawQuadTexture(const Ref<Texture2D>& pTexture, const glm::mat4& world, const glm::vec4& texCoords)
	//{
	//	//Update vertex buffer data
	//	SetUVsAndDefaultPos(texCoords);
	//	m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));

	//	//Update shader variables
	//	m_Data2D->TextureShader->Bind();
	//	m_Data2D->TextureShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
	//	m_Data2D->TextureShader->LoadMat4("u_World", world);

	//	//Bind the texture to use
	//	pTexture->Bind();

	//	//Bind the vertex array for drawing
	//	m_Data2D->NormalVertexArray->Bind();
	//	RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);
	//}

	//void Renderer2D::DrawQuadFlatColor(const glm::vec4& color, const glm::mat4& world)
	//{
	//	//Update shader variables
	//	m_Data2D->ColorShader->Bind();
	//	m_Data2D->ColorShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
	//	m_Data2D->ColorShader->LoadMat4("u_World", world);
	//	m_Data2D->ColorShader->LoadFloat4("u_Color", color);

	//	//Bind the vertex array for drawing
	//	m_Data2D->NormalVertexArray->Bind();
	//	RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);
	//}

	//void Renderer2D::DrawQuadFlatColor(const glm::vec4& color)
	//{
	//	glm::mat4 world = glm::scale(glm::mat4(1.f), { 32.f, 32.f, 1.f });
	//	//Update shader variables
	//	m_Data2D->ColorShader->Bind();
	//	m_Data2D->ColorShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
	//	m_Data2D->ColorShader->LoadMat4("u_World", world);
	//	m_Data2D->ColorShader->LoadFloat4("u_Color", color);

	//	//Bind the vertex array for drawing
	//	m_Data2D->NormalVertexArray->Bind();
	//	RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);
	//}

	//void Renderer2D::SubmitBufferData(const glm::vec4& uvs)
	//{
	//	SetUVsAndDefaultPos(uvs);
	//	m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));
	//}

	//void Renderer2D::SubmitBufferData(const std::vector<glm::vec2>& vertices)
	//{
	//	SetVertices(vertices);
	//	m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));
	//}

	//void Renderer2D::DrawString(std::string const& fontName, std::string const& text, const glm::mat4& world, const glm::vec4& color)
	//{
	//	auto& fontChars = m_Data2D->Fonts->GetFontCharacters(fontName);
	//	float x = 0;
	//	for (auto c = text.begin(); c != text.end(); ++c)
	//	{
	//		Character chr = fontChars[*c];
	//		float xpos = x + chr.Offset.x;
	//		float ypos = 26.f / 32.f - chr.Offset.y;

	//		float w = chr.Size.x;
	//		float h = chr.Size.y;
	//		m_Data2D->Vertices[0].Position = { xpos, ypos - h, 0.f };
	//		m_Data2D->Vertices[0].Uv = { chr.Uv.x, 1 - chr.Uv.z };
	//		m_Data2D->Vertices[1].Position = { xpos, ypos, 0.f };
	//		m_Data2D->Vertices[1].Uv = { chr.Uv.x, 1 - chr.Uv.w };
	//		m_Data2D->Vertices[2].Position = { xpos + w, ypos, 0.f };
	//		m_Data2D->Vertices[2].Uv = { chr.Uv.y, 1 - chr.Uv.w };
	//		m_Data2D->Vertices[3].Position = { xpos + w, ypos - h, 0.f };
	//		m_Data2D->Vertices[3].Uv = { chr.Uv.y, 1 - chr.Uv.z };

	//		m_Data2D->Fonts->Bind(fontName);
	//		m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));

	//		m_Data2D->TextShader->Bind();
	//		m_Data2D->TextShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
	//		m_Data2D->TextShader->LoadMat4("u_World", world);
	//		m_Data2D->TextShader->LoadFloat4("u_Color", color);

	//		m_Data2D->Fonts->GetFontTexture(fontName)->Bind();

	//		m_Data2D->NormalVertexArray->Bind();
	//		RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);

	//		x += chr.AdvanceX;
	//	}
	//}

	//void Renderer2D::LoadFont(std::string const& filepath)
	//{
	//	m_Data2D->Fonts->LoadFont(filepath);
	//}

	//bool Renderer2D::HasFont(std::string const& fontname)
	//{
	//	return m_Data2D->Fonts->HasTexture(fontname);
	//}

	//void Renderer2D::SetUVsAndDefaultPos(const glm::vec4& uv)
	//{

	//	m_Data2D->Vertices[0].Position = { 0.f, 0.f, 0.f };
	//	m_Data2D->Vertices[1].Position = { 0.f, 1.f, 0.f };
	//	m_Data2D->Vertices[2].Position = { 1.f, 1.f, 0.f };
	//	m_Data2D->Vertices[3].Position = { 1.f, 0.f, 0.f };

	//	m_Data2D->Vertices[0].Uv = { uv.x, uv.z };
	//	m_Data2D->Vertices[1].Uv = { uv.x, uv.w };
	//	m_Data2D->Vertices[2].Uv = { uv.y, uv.w };
	//	m_Data2D->Vertices[3].Uv = { uv.y, uv.z };
	//}

	//void Renderer2D::SetVertices(const std::vector<glm::vec2>& vertices)
	//{
	//	glm::vec2 pos = vertices[0];
	//	m_Data2D->Vertices[0].Position = { pos.x, pos.y, 0.f };
	//	pos = vertices[1];
	//	m_Data2D->Vertices[1].Position = { pos.x, pos.y, 0.f };
	//	pos = vertices[2];
	//	m_Data2D->Vertices[2].Position = { pos.x, pos.y, 0.f };
	//	pos = vertices[3];
	//	m_Data2D->Vertices[3].Position = { pos.x, pos.y, 0.f };

	//	m_Data2D->Vertices[0].Uv = { 0.f, 0.f };
	//	m_Data2D->Vertices[1].Uv = { 0.f, 1.f };
	//	m_Data2D->Vertices[2].Uv = { 1.f, 1.f };
	//	m_Data2D->Vertices[3].Uv = { 1.f, 0.f };
	//}
}
