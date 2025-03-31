#include "ImpPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Imp
{
	Scope<RendererApi> RenderCommand::m_pRendererAPI = std::make_unique<OpenGLRendererAPI>();
}