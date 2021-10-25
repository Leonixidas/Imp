#include "ImpPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Imp/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Imp::Ref<Imp::VertexArray> Imp::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
	default:
		IMP_CORE_FATAL("API with id: {0} is not supported!", Renderer::GetAPI());
		return nullptr;
	}

}