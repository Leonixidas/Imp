#include "ImpPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Imp/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Imp::Ref<Imp::VertexArray> Imp::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: IMP_ERROR("NONE as API is not supported"); return nullptr;
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
	}

	IMP_ERROR("Unknown Render API");

	return nullptr;
}