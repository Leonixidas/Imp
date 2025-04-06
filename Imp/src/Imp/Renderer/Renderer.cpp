#include "ImpPCH.h"
#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer2D.h"
#include "Vertex.h"


namespace Imp
{
Scope<Renderer::SceneData> Renderer::m_SceneData = std::make_unique<Renderer::SceneData>();
Scope<Renderer2D::SceneData2D> Renderer2D::m_Data2D = std::make_unique<Renderer2D::SceneData2D>();

void Renderer::Init()
{
	RenderCommand::Init();
}

void Renderer::BeginScene(Ref<Camera> const& pCam)
{
	m_SceneData->Camera = pCam;
}

void Renderer::EndScene()
{

}

uint32_t Renderer::GetFrame()
{
	return RenderCommand::GetFrame();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}


//*******************************************************//
//**********************RENDERER2D***********************//
//*******************************************************//

void Renderer2D::Init()
{
	RenderCommand::Init();
}

void Renderer2D::ShutDown()
{
}

void Renderer2D::EndScene()
{
}

void Renderer2D::DrawQuadTexture(const Ref<Texture2D>& pTexture, const glm::mat4& world, const glm::vec4& texCoords)
{
	//Update vertex buffer data
	SetUVsAndDefaultPos(texCoords);
	m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));

	//Update shader variables
	m_Data2D->TextureShader->Bind();
	m_Data2D->TextureShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
	m_Data2D->TextureShader->LoadMat4("u_World", world);

	//Bind the texture to use
	pTexture->Bind();

	//Bind the vertex array for drawing
	m_Data2D->NormalVertexArray->Bind();
	RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);
}

void Renderer2D::DrawQuadFlatColor(const glm::vec4& color, const glm::mat4& world)
{
	//Update shader variables
	m_Data2D->ColorShader->Bind();
	m_Data2D->ColorShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
	m_Data2D->ColorShader->LoadMat4("u_World", world);
	m_Data2D->ColorShader->LoadFloat4("u_Color", color);

	//Bind the vertex array for drawing
	m_Data2D->NormalVertexArray->Bind();
	RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);
}

void Renderer2D::DrawQuadFlatColor(const glm::vec4& color)
{
	glm::mat4 world = glm::scale(glm::mat4(1.f), { 32.f, 32.f, 1.f });
	//Update shader variables
	m_Data2D->ColorShader->Bind();
	m_Data2D->ColorShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
	m_Data2D->ColorShader->LoadMat4("u_World", world);
	m_Data2D->ColorShader->LoadFloat4("u_Color", color);

	//Bind the vertex array for drawing
	m_Data2D->NormalVertexArray->Bind();
	RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);
}

void Renderer2D::SubmitBufferData(const glm::vec4& uvs)
{
	SetUVsAndDefaultPos(uvs);
	m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));
}

void Renderer2D::SubmitBufferData(const std::vector<glm::vec2>& vertices)
{
	SetVertices(vertices);
	m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));
}

void Renderer2D::DrawString(std::string const& fontName, std::string const& text, const glm::mat4& world, const glm::vec4& color)
{
	auto& fontChars = m_Data2D->Fonts->GetFontCharacters(fontName);
	float x = 0;
	for (auto c = text.begin(); c != text.end(); ++c)
	{
		Character chr = fontChars[*c];
		float xpos = x + chr.Offset.x;
		float ypos = 26.f / 32.f - chr.Offset.y;

		float w = chr.Size.x;
		float h = chr.Size.y;
		m_Data2D->Vertices[0].Position = { xpos, ypos - h, 0.f };
		m_Data2D->Vertices[0].Uv = {chr.Uv.x, 1 - chr.Uv.z};
		m_Data2D->Vertices[1].Position = { xpos, ypos, 0.f };
		m_Data2D->Vertices[1].Uv = { chr.Uv.x, 1 - chr.Uv.w };
		m_Data2D->Vertices[2].Position = { xpos + w, ypos, 0.f };
		m_Data2D->Vertices[2].Uv = { chr.Uv.y, 1 - chr.Uv.w };
		m_Data2D->Vertices[3].Position = { xpos + w, ypos - h, 0.f };
		m_Data2D->Vertices[3].Uv = { chr.Uv.y, 1 - chr.Uv.z };

		m_Data2D->Fonts->Bind(fontName);
		m_Data2D->NormalVertexArray->SubmitBufferData(0, glm::value_ptr(m_Data2D->Vertices[0].Position), uint32_t(m_Data2D->Vertices.size() * sizeof(Vertex)));

		m_Data2D->TextShader->Bind();
		m_Data2D->TextShader->LoadMat4("u_ViewProjection", m_Data2D->OrthoCamera->GetViewProjectionMatrix());
		m_Data2D->TextShader->LoadMat4("u_World", world);
		m_Data2D->TextShader->LoadFloat4("u_Color", color);

		m_Data2D->Fonts->GetFontTexture(fontName)->Bind();

		m_Data2D->NormalVertexArray->Bind();
		RenderCommand::DrawIndexed(m_Data2D->NormalVertexArray);

		x += chr.AdvanceX;
	}
}

void Renderer2D::LoadFont(std::string const& filepath)
{
	m_Data2D->Fonts->LoadFont(filepath);
}

bool Renderer2D::HasFont(std::string const& fontname)
{
	return m_Data2D->Fonts->HasTexture(fontname);
}

void Renderer2D::SetUVsAndDefaultPos(const glm::vec4& uv)
{

	m_Data2D->Vertices[0].Position = { 0.f, 0.f, 0.f };
	m_Data2D->Vertices[1].Position = { 0.f, 1.f, 0.f };
	m_Data2D->Vertices[2].Position = { 1.f, 1.f, 0.f };
	m_Data2D->Vertices[3].Position = { 1.f, 0.f, 0.f };

	m_Data2D->Vertices[0].Uv = { uv.x, uv.z };
	m_Data2D->Vertices[1].Uv = { uv.x, uv.w };
	m_Data2D->Vertices[2].Uv = { uv.y, uv.w };
	m_Data2D->Vertices[3].Uv = { uv.y, uv.z };
}

void Renderer2D::SetVertices(const std::vector<glm::vec2>& vertices)
{
	glm::vec2 pos = vertices[0];
	m_Data2D->Vertices[0].Position = {pos.x, pos.y, 0.f };
	pos = vertices[1];
	m_Data2D->Vertices[1].Position = { pos.x, pos.y, 0.f };
	pos = vertices[2];
	m_Data2D->Vertices[2].Position = { pos.x, pos.y, 0.f };
	pos = vertices[3];
	m_Data2D->Vertices[3].Position = { pos.x, pos.y, 0.f };

	m_Data2D->Vertices[0].Uv = { 0.f, 0.f};
	m_Data2D->Vertices[1].Uv = { 0.f, 1.f};
	m_Data2D->Vertices[2].Uv = { 1.f, 1.f};
	m_Data2D->Vertices[3].Uv = { 1.f, 0.f};
}
}
