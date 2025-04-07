#include "ImpPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Imp
{
	Scope<RendererApi> RenderCommand::s_RendererAPI = RendererApi::Create();
}