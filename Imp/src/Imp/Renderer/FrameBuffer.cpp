#include "ImpPCH.h"
#include "Imp/Renderer/FrameBuffer.h"
#include "Imp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Imp
{
	Ref<FrameBuffer> FrameBuffer::Create(FrameBufferSpecification const& spec)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None:    IMP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererApi::Api::OpenGl:  return CreateRef<OpenGLFrameBuffer>(spec);
		}

		IMP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
