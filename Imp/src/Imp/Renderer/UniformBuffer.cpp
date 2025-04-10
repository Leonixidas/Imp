#include "ImpPCH.h"
#include "UniformBuffer.h"
#include "Imp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Imp
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetApi())
		{
		case RendererApi::Api::None: IMP_CORE_ASSERT(false, "RendererApi::None is currently not supported!"); return nullptr;
		case RendererApi::Api::OpenGl: return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		IMP_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}

}