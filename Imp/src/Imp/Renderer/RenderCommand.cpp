#include "ImpPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Imp
{
	Scope<RendererAPI> RenderCommand::mpRendererAPI = std::make_unique<OpenGLRendererAPI>();
}