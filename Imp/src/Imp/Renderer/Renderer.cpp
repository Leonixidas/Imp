#include "ImpPCH.h"
#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Imp
{
	Scope<Renderer::SceneData> Renderer::m_pSceneData = std::make_unique<Renderer::SceneData>();
	Scope<Renderer2D::SceneData2D> Renderer2D::m_p2DData = std::make_unique<Renderer2D::SceneData2D>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(const Ref<Camera>& pCam)
	{
		m_pSceneData->pCamera = pCam;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->LoadSVMat4("u_ViewProjection", m_pSceneData->pCamera->GetViewProjectionMatrix());
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	//*******************************************************//
	//**********************RENDERER2D***********************//
	//*******************************************************//

	void Renderer2D::Init()
	{
		RenderCommand::Init();
		//VertexArray
		m_p2DData->m_pVertexArray = VertexArray::Create();

		m_p2DData->m_Vertices.reserve(4);
		//VertexBuffer
		Vertex v{};
		v.Position = { 0.f,0.f,0.f };
		v.uv = { 0.f,0.f };
		m_p2DData->m_Vertices.push_back(v);
		v.Position = { 0.f,1.f,0.f };
		v.uv = { 0.f,1.f };
		m_p2DData->m_Vertices.push_back(v);
		v.Position = { 1.f,1.f,0.f };
		v.uv = { 1.f,1.f };
		m_p2DData->m_Vertices.push_back(v);
		v.Position = { 1.f,0.f,0.f };
		v.uv = { 1.f,0.f };
		m_p2DData->m_Vertices.push_back(v);

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(glm::value_ptr(m_p2DData->m_Vertices.data()->Position), uint32_t(m_p2DData->m_Vertices.size() * sizeof(Vertex)));
		Imp::BufferLayout layout = {
			{ShaderDataType::Float3, "vPosition"},
			{ShaderDataType::Float2, "vUV"}
		};

		vertexBuffer->SetLayout(layout);

		m_p2DData->m_pVertexArray->AddVertexBuffer(vertexBuffer);

		//IndexBuffer
		uint32_t indices[6] = { 0,1,2,0,2,3 };
		m_p2DData->m_pVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_p2DData->m_pTextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		m_p2DData->m_pColorShader = Shader::Create("Assets/Shaders/Color.glsl");
		m_p2DData->m_pTextShader = Shader::Create("Assets/Shaders/Text.glsl");
		m_p2DData->m_pFonts = FontTexture::Create();

		m_p2DData->m_pTextureShader->Bind();
		m_p2DData->m_pTextureShader->LoadSVInt("u_Texture", 0);

		m_p2DData->m_pTextShader->Bind();
		m_p2DData->m_pTextShader->LoadSVInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
	}

	void Renderer2D::BeginScene(const Ref<OrthographicCamera>& pCam)
	{
		m_p2DData->m_pOrthoCamera = pCam;
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::CreateInstancedBuffer(std::vector<glm::mat4>& matrices)
	{
		Ref<VertexBuffer> vert = VertexBuffer::Create(&matrices[0][0][0], uint32_t(matrices.size() * sizeof(glm::mat4)));
		
		Imp::BufferLayout layout = {
			{ShaderDataType::Mat4, "vWorld"}
		};

		m_p2DData->m_pInstanceVertexArray->AddInstancedBuffer(vert, m_p2DData->m_pTextureInstShader->GetAttributeLocation("vWorld"));
	}

	void Renderer2D::Submit(const Ref<VertexArray>& pVertexArray, const Ref<Texture2D>& pTexture, const glm::mat4& world)
	{
		pTexture->Bind();
		m_p2DData->m_pTextureShader->Bind();
		m_p2DData->m_pTextureShader->LoadSVMat4("u_ViewProjection", m_p2DData->m_pOrthoCamera->GetViewProjectionMatrix());
		m_p2DData->m_pTextureShader->LoadSVMat4("u_World", world);
		pVertexArray->Bind();
		RenderCommand::DrawIndexed(pVertexArray);
	}

	void Renderer2D::DrawQuadTexture(const Ref<Texture2D>& pTexture, const glm::mat4& world, const glm::vec4& texCoords)
	{
		//Update vertex buffer data
		SetUVsAndDefaultPos(texCoords);
		m_p2DData->m_pVertexArray->SubmitBufferData(0, glm::value_ptr(m_p2DData->m_Vertices[0].Position), uint32_t(m_p2DData->m_Vertices.size() * sizeof(Vertex)));
		
		//Update shader variables
		m_p2DData->m_pTextureShader->Bind();
		m_p2DData->m_pTextureShader->LoadSVMat4("u_ViewProjection", m_p2DData->m_pOrthoCamera->GetViewProjectionMatrix());
		m_p2DData->m_pTextureShader->LoadSVMat4("u_World", world);
		
		//Bind the texture to use
		pTexture->Bind();

		//Bind the vertex array for drawing
		m_p2DData->m_pVertexArray->Bind();
		RenderCommand::DrawIndexed(m_p2DData->m_pVertexArray);
	}

	void Renderer2D::DrawQuadFlatColor(const glm::vec4& color, const glm::mat4& world)
	{
		//Update shader variables
		m_p2DData->m_pColorShader->Bind();
		m_p2DData->m_pColorShader->LoadSVMat4("u_ViewProjection", m_p2DData->m_pOrthoCamera->GetViewProjectionMatrix());
		m_p2DData->m_pColorShader->LoadSVMat4("u_World", world);
		m_p2DData->m_pColorShader->LoadSVFloat4("u_Color", color);

		//Bind the vertex array for drawing
		m_p2DData->m_pVertexArray->Bind();
		RenderCommand::DrawIndexed(m_p2DData->m_pVertexArray);
	}

	void Renderer2D::DrawQuadFlatColor(const glm::vec4& color)
	{
		glm::mat4 world = glm::scale(glm::mat4(1.f), { 32.f,32.f,1.f });
		//Update shader variables
		m_p2DData->m_pColorShader->Bind();
		m_p2DData->m_pColorShader->LoadSVMat4("u_ViewProjection", m_p2DData->m_pOrthoCamera->GetViewProjectionMatrix());
		m_p2DData->m_pColorShader->LoadSVMat4("u_World", world);
		m_p2DData->m_pColorShader->LoadSVFloat4("u_Color", color);

		//Bind the vertex array for drawing
		m_p2DData->m_pVertexArray->Bind();
		RenderCommand::DrawIndexed(m_p2DData->m_pVertexArray);
	}

	void Renderer2D::DrawQuadInstanced(const Ref<Texture2D>& pTexture, const std::vector<glm::mat4>& matrices, const glm::vec4& texCoords)
	{
		//Update shader variables
		m_p2DData->m_pTextureInstShader->Bind();
		m_p2DData->m_pTextureInstShader->LoadSVMat4("u_ViewProjection", m_p2DData->m_pOrthoCamera->GetViewProjectionMatrix());

		for(size_t i = 0; i < matrices.size(); ++i)
			m_p2DData->m_pTextureInstShader->LoadSVMat4("u_Matrices[" + std::to_string(i) + ']', matrices[i]);

		//Bind the texture to use
		pTexture->Bind();

		//Bind the vertex array for drawing
		m_p2DData->m_pVertexArray->Bind();
		RenderCommand::DrawInstanced(m_p2DData->m_pVertexArray, uint32_t(matrices.size()));
	}

	void Renderer2D::SubmitInstancedBufferData(std::vector<glm::mat4>& world)
	{
	}

	void Renderer2D::SubmitBufferData(const glm::vec4& uvs)
	{
		SetUVsAndDefaultPos(uvs);
		m_p2DData->m_pVertexArray->SubmitBufferData(0, glm::value_ptr(m_p2DData->m_Vertices[0].Position), uint32_t(m_p2DData->m_Vertices.size() * sizeof(Vertex)));
	}

	void Renderer2D::SubmitBufferData(const std::vector<glm::vec2>& vertices)
	{
		SetVertices(vertices);
		m_p2DData->m_pVertexArray->SubmitBufferData(0, glm::value_ptr(m_p2DData->m_Vertices[0].Position), uint32_t(m_p2DData->m_Vertices.size() * sizeof(Vertex)));
	}

	void Renderer2D::DrawString(const std::string& fontName, const std::string& text, const glm::mat4& world, const glm::vec4& color)
	{
		auto& fontChars = m_p2DData->m_pFonts->GetFontCharacters(fontName);
		float x = 0;
		for (auto c = text.begin(); c != text.end(); ++c)
		{
			Character chr = fontChars[*c];
			float xpos = x + chr.Offset.x;
			float ypos = 26/32 - chr.Offset.y;

			float w = chr.Size.x;
			float h = chr.Size.y;
			m_p2DData->m_Vertices[0].Position = { xpos, ypos - h, 0.f };
			m_p2DData->m_Vertices[0].uv = {chr.uv.x, 1 - chr.uv.z};
			m_p2DData->m_Vertices[1].Position = { xpos, ypos, 0.f };
			m_p2DData->m_Vertices[1].uv = { chr.uv.x, 1 - chr.uv.w };
			m_p2DData->m_Vertices[2].Position = { xpos + w, ypos, 0.f };
			m_p2DData->m_Vertices[2].uv = { chr.uv.y, 1 - chr.uv.w };
			m_p2DData->m_Vertices[3].Position = { xpos + w, ypos - h, 0.f };
			m_p2DData->m_Vertices[3].uv = { chr.uv.y, 1 - chr.uv.z };

			m_p2DData->m_pFonts->Bind(fontName);
			m_p2DData->m_pVertexArray->SubmitBufferData(0, glm::value_ptr(m_p2DData->m_Vertices[0].Position), uint32_t(m_p2DData->m_Vertices.size() * sizeof(Vertex)));

			m_p2DData->m_pTextShader->Bind();
			m_p2DData->m_pTextShader->LoadSVMat4("u_ViewProjection", m_p2DData->m_pOrthoCamera->GetViewProjectionMatrix());
			m_p2DData->m_pTextShader->LoadSVMat4("u_World", world);
			m_p2DData->m_pTextShader->LoadSVFloat4("u_Color", color);

			m_p2DData->m_pFonts->GetFontTexture(fontName)->Bind();

			m_p2DData->m_pVertexArray->Bind();
			RenderCommand::DrawIndexed(m_p2DData->m_pVertexArray);

			x += chr.AdvanceX;
		}
	}

	void Renderer2D::LoadFont(const std::string& filepath)
	{
		m_p2DData->m_pFonts->LoadFont(filepath);
	}

	bool Renderer2D::HasFont(const std::string& fontname)
	{
		return m_p2DData->m_pFonts->HasTexture(fontname);
	}

	void Renderer2D::SetUVsAndDefaultPos(const glm::vec4& uv)
	{

		m_p2DData->m_Vertices[0].Position = { 0.f,0.f,0.f };
		m_p2DData->m_Vertices[1].Position = { 0.f,1.f,0.f };
		m_p2DData->m_Vertices[2].Position = { 1.f,1.f,0.f };
		m_p2DData->m_Vertices[3].Position = { 1.f,0.f,0.f };

		m_p2DData->m_Vertices[0].uv = { uv.x, uv.z };
		m_p2DData->m_Vertices[1].uv = { uv.x, uv.w };
		m_p2DData->m_Vertices[2].uv = { uv.y, uv.w };
		m_p2DData->m_Vertices[3].uv = { uv.y, uv.z };
	}

	void Renderer2D::SetVertices(const std::vector<glm::vec2>& vertices)
	{
		glm::vec2 pos = vertices[0];
		m_p2DData->m_Vertices[0].Position = {pos.x,pos.y,0.f };
		pos = vertices[1];
		m_p2DData->m_Vertices[1].Position = { pos.x,pos.y,0.f };
		pos = vertices[2];
		m_p2DData->m_Vertices[2].Position = { pos.x,pos.y,0.f };
		pos = vertices[3];
		m_p2DData->m_Vertices[3].Position = { pos.x,pos.y,0.f };

		m_p2DData->m_Vertices[0].uv = { 0.f, 0.f};
		m_p2DData->m_Vertices[1].uv = { 0.f, 1.f};
		m_p2DData->m_Vertices[2].uv = { 1.f, 1.f};
		m_p2DData->m_Vertices[3].uv = { 1.f, 0.f};
	}
}