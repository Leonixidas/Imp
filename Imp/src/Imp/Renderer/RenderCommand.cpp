#include "ImpPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Imp
{
	RendererAPI* RenderCommand::m_pRendererAPI = new OpenGLRendererAPI();
}