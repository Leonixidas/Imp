#include "ImpPCH.h"
#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer2D.h"
#include "Vertex.h"


namespace Imp
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::ShutDown()
	{
		Renderer2D::ShutDown();
	}

	void Renderer::OnWindowResize(uint32_t const width, uint32_t const height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera const& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(Ref<Shader> const& shader, Ref<VertexArray> const& vertexArray, glm::mat4 const& transform)
	{
		shader->Bind();
		shader->LoadMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->LoadMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{

	}

	uint32_t Renderer::GetFrame()
	{
		return RenderCommand::GetFrame();
	}

	

}
