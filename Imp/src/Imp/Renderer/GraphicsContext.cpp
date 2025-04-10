#include "ImpPCH.h"
#include "GraphicsContext.h"

#include "Imp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Imp
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:    IMP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererApi::Api::OpenGl:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		IMP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
