#include "ImpPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Imp/Core/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Imp::Ref<Imp::VertexArray> Imp::VertexArray::Create()
{
	switch (Renderer::GetApi())
	{
	case RendererApi::Api::OpenGl: return std::make_shared<OpenGLVertexArray>();
	default:
		IMP_CORE_FATAL("API with id: {0} is not supported!", static_cast<int>(Renderer::GetApi()));
		return nullptr;
	}

}