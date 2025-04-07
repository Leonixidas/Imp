#include "ImpPCH.h"
#include "RendererApi.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Imp
{
	RendererApi::Api RendererApi::s_Api = RendererApi::Api::OpenGl;

	Scope<RendererApi> RendererApi::Create()
	{
		switch (s_Api)
		{
		case RendererApi::Api::None: IMP_CORE_ASSERT(false, "RendererApi::None is currently not supported!"); return nullptr;
		case RendererApi::Api::OpenGl: return CreateScope<OpenGLRendererAPI>();
		}

		IMP_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}

}
