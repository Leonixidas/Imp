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

}
