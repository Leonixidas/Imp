#include "ImpPCH.h"
#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Imp
{
	Scope<Renderer::SceneData> Renderer::mpSceneData = std::make_unique<Renderer::SceneData>();
	Scope<Renderer2D::SceneData2D> Renderer2D::mp2DData = std::make_unique<Renderer2D::SceneData2D>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(const Ref<Camera>& pCam)
	{
		mpSceneData->pCamera = pCam;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->LoadSVMat4("u_ViewProjection", mpSceneData->pCamera->GetViewProjectionMatrix());
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void* Renderer::GetFrame()
	{
		return RenderCommand::GetFrame();
	}


	//*******************************************************//
	//**********************RENDERER2D***********************//
	//*******************************************************//

	void Renderer2D::Init()
	{
		RenderCommand::Init();
		////VertexArray
		//mp2DData->mpVertexArray = VertexArray::Create();

		//mp2DData->mVertices.reserve(4);
		////VertexBuffer
		//Vertex v{};
		//v.Position = { 0.f,0.f,0.f };
		//v.uv = { 0.f,0.f };
		//mp2DData->mVertices.push_back(v);
		//v.Position = { 0.f,1.f,0.f };
		//v.uv = { 0.f,1.f };
		//mp2DData->mVertices.push_back(v);
		//v.Position = { 1.f,1.f,0.f };
		//v.uv = { 1.f,1.f };
		//mp2DData->mVertices.push_back(v);
		//v.Position = { 1.f,0.f,0.f };
		//v.uv = { 1.f,0.f };
		//mp2DData->mVertices.push_back(v);

		//Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(glm::value_ptr(mp2DData->mVertices.data()->Position), uint32_t(mp2DData->mVertices.size() * sizeof(Vertex)));
		//Imp::BufferLayout layout = {
		//	{ShaderDataType::Float3, "vPosition"},
		//	{ShaderDataType::Float2, "vUV"}
		//};

		//vertexBuffer->SetLayout(layout);

		//mp2DData->mpVertexArray->AddVertexBuffer(vertexBuffer);

		////IndexBuffer
		//uint32_t indices[6] = { 0,1,2,0,2,3 };
		//mp2DData->mpVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		//mp2DData->mpTextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		//mp2DData->mpColorShader = Shader::Create("Assets/Shaders/Color.glsl");
		//mp2DData->mpTextShader = Shader::Create("Assets/Shaders/Text.glsl");
		//mp2DData->mpFonts = FontTexture::Create();

		//mp2DData->mpTextureShader->Bind();
		//mp2DData->mpTextureShader->LoadSVInt("u_Texture", 0);

		//mp2DData->mpTextShader->Bind();
		//mp2DData->mpTextShader->LoadSVInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
	}

	void Renderer2D::BeginScene(const Ref<OrthographicCamera>& pCam)
	{
		mp2DData->mpOrthoCamera = pCam;
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

		mp2DData->mpInstanceVertexArray->AddInstancedBuffer(vert, mp2DData->mpTextureInstShader->GetAttributeLocation("vWorld"));
	}

	void Renderer2D::Submit(const Ref<VertexArray>& pVertexArray, const Ref<Texture2D>& pTexture, const glm::mat4& world)
	{
		pTexture->Bind();
		mp2DData->mpTextureShader->Bind();
		mp2DData->mpTextureShader->LoadSVMat4("u_ViewProjection", mp2DData->mpOrthoCamera->GetViewProjectionMatrix());
		mp2DData->mpTextureShader->LoadSVMat4("u_World", world);
		pVertexArray->Bind();
		RenderCommand::DrawIndexed(pVertexArray);
	}

	void Renderer2D::DrawQuadTexture(const Ref<Texture2D>& pTexture, const glm::mat4& world, const glm::vec4& texCoords)
	{
		//Update vertex buffer data
		SetUVsAndDefaultPos(texCoords);
		mp2DData->mpVertexArray->SubmitBufferData(0, glm::value_ptr(mp2DData->mVertices[0].Position), uint32_t(mp2DData->mVertices.size() * sizeof(Vertex)));
		
		//Update shader variables
		mp2DData->mpTextureShader->Bind();
		mp2DData->mpTextureShader->LoadSVMat4("u_ViewProjection", mp2DData->mpOrthoCamera->GetViewProjectionMatrix());
		mp2DData->mpTextureShader->LoadSVMat4("u_World", world);
		
		//Bind the texture to use
		pTexture->Bind();

		//Bind the vertex array for drawing
		mp2DData->mpVertexArray->Bind();
		RenderCommand::DrawIndexed(mp2DData->mpVertexArray);
	}

	void Renderer2D::DrawQuadFlatColor(const glm::vec4& color, const glm::mat4& world)
	{
		//Update shader variables
		mp2DData->mpColorShader->Bind();
		mp2DData->mpColorShader->LoadSVMat4("u_ViewProjection", mp2DData->mpOrthoCamera->GetViewProjectionMatrix());
		mp2DData->mpColorShader->LoadSVMat4("u_World", world);
		mp2DData->mpColorShader->LoadSVFloat4("u_Color", color);

		//Bind the vertex array for drawing
		mp2DData->mpVertexArray->Bind();
		RenderCommand::DrawIndexed(mp2DData->mpVertexArray);
	}

	void Renderer2D::DrawQuadFlatColor(const glm::vec4& color)
	{
		glm::mat4 world = glm::scale(glm::mat4(1.f), { 32.f,32.f,1.f });
		//Update shader variables
		mp2DData->mpColorShader->Bind();
		mp2DData->mpColorShader->LoadSVMat4("u_ViewProjection", mp2DData->mpOrthoCamera->GetViewProjectionMatrix());
		mp2DData->mpColorShader->LoadSVMat4("u_World", world);
		mp2DData->mpColorShader->LoadSVFloat4("u_Color", color);

		//Bind the vertex array for drawing
		mp2DData->mpVertexArray->Bind();
		RenderCommand::DrawIndexed(mp2DData->mpVertexArray);
	}

	void Renderer2D::DrawQuadInstanced(const Ref<Texture2D>& pTexture, const std::vector<glm::mat4>& matrices, const glm::vec4& texCoords)
	{
		//Update shader variables
		mp2DData->mpTextureInstShader->Bind();
		mp2DData->mpTextureInstShader->LoadSVMat4("u_ViewProjection", mp2DData->mpOrthoCamera->GetViewProjectionMatrix());

		for(size_t i = 0; i < matrices.size(); ++i)
			mp2DData->mpTextureInstShader->LoadSVMat4("u_Matrices[" + std::to_string(i) + ']', matrices[i]);

		//Bind the texture to use
		pTexture->Bind();

		//Bind the vertex array for drawing
		mp2DData->mpVertexArray->Bind();
		RenderCommand::DrawInstanced(mp2DData->mpVertexArray, uint32_t(matrices.size()));
	}

	void Renderer2D::SubmitInstancedBufferData(std::vector<glm::mat4>& world)
	{
	}

	void Renderer2D::SubmitBufferData(const glm::vec4& uvs)
	{
		SetUVsAndDefaultPos(uvs);
		mp2DData->mpVertexArray->SubmitBufferData(0, glm::value_ptr(mp2DData->mVertices[0].Position), uint32_t(mp2DData->mVertices.size() * sizeof(Vertex)));
	}

	void Renderer2D::SubmitBufferData(const std::vector<glm::vec2>& vertices)
	{
		SetVertices(vertices);
		mp2DData->mpVertexArray->SubmitBufferData(0, glm::value_ptr(mp2DData->mVertices[0].Position), uint32_t(mp2DData->mVertices.size() * sizeof(Vertex)));
	}

	void Renderer2D::DrawString(const std::string& fontName, const std::string& text, const glm::mat4& world, const glm::vec4& color)
	{
		auto& fontChars = mp2DData->mpFonts->GetFontCharacters(fontName);
		float x = 0;
		for (auto c = text.begin(); c != text.end(); ++c)
		{
			Character chr = fontChars[*c];
			float xpos = x + chr.Offset.x;
			float ypos = 26/32 - chr.Offset.y;

			float w = chr.Size.x;
			float h = chr.Size.y;
			mp2DData->mVertices[0].Position = { xpos, ypos - h, 0.f };
			mp2DData->mVertices[0].uv = {chr.uv.x, 1 - chr.uv.z};
			mp2DData->mVertices[1].Position = { xpos, ypos, 0.f };
			mp2DData->mVertices[1].uv = { chr.uv.x, 1 - chr.uv.w };
			mp2DData->mVertices[2].Position = { xpos + w, ypos, 0.f };
			mp2DData->mVertices[2].uv = { chr.uv.y, 1 - chr.uv.w };
			mp2DData->mVertices[3].Position = { xpos + w, ypos - h, 0.f };
			mp2DData->mVertices[3].uv = { chr.uv.y, 1 - chr.uv.z };

			mp2DData->mpFonts->Bind(fontName);
			mp2DData->mpVertexArray->SubmitBufferData(0, glm::value_ptr(mp2DData->mVertices[0].Position), uint32_t(mp2DData->mVertices.size() * sizeof(Vertex)));

			mp2DData->mpTextShader->Bind();
			mp2DData->mpTextShader->LoadSVMat4("u_ViewProjection", mp2DData->mpOrthoCamera->GetViewProjectionMatrix());
			mp2DData->mpTextShader->LoadSVMat4("u_World", world);
			mp2DData->mpTextShader->LoadSVFloat4("u_Color", color);

			mp2DData->mpFonts->GetFontTexture(fontName)->Bind();

			mp2DData->mpVertexArray->Bind();
			RenderCommand::DrawIndexed(mp2DData->mpVertexArray);

			x += chr.AdvanceX;
		}
	}

	void Renderer2D::LoadFont(const std::string& filepath)
	{
		mp2DData->mpFonts->LoadFont(filepath);
	}

	bool Renderer2D::HasFont(const std::string& fontname)
	{
		return mp2DData->mpFonts->HasTexture(fontname);
	}

	void Renderer2D::SetUVsAndDefaultPos(const glm::vec4& uv)
	{

		mp2DData->mVertices[0].Position = { 0.f,0.f,0.f };
		mp2DData->mVertices[1].Position = { 0.f,1.f,0.f };
		mp2DData->mVertices[2].Position = { 1.f,1.f,0.f };
		mp2DData->mVertices[3].Position = { 1.f,0.f,0.f };

		mp2DData->mVertices[0].uv = { uv.x, uv.z };
		mp2DData->mVertices[1].uv = { uv.x, uv.w };
		mp2DData->mVertices[2].uv = { uv.y, uv.w };
		mp2DData->mVertices[3].uv = { uv.y, uv.z };
	}

	void Renderer2D::SetVertices(const std::vector<glm::vec2>& vertices)
	{
		glm::vec2 pos = vertices[0];
		mp2DData->mVertices[0].Position = {pos.x,pos.y,0.f };
		pos = vertices[1];
		mp2DData->mVertices[1].Position = { pos.x,pos.y,0.f };
		pos = vertices[2];
		mp2DData->mVertices[2].Position = { pos.x,pos.y,0.f };
		pos = vertices[3];
		mp2DData->mVertices[3].Position = { pos.x,pos.y,0.f };

		mp2DData->mVertices[0].uv = { 0.f, 0.f};
		mp2DData->mVertices[1].uv = { 0.f, 1.f};
		mp2DData->mVertices[2].uv = { 1.f, 1.f};
		mp2DData->mVertices[3].uv = { 1.f, 0.f};
	}
}