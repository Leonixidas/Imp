#include "ImpPCH.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

Imp::Ref<Imp::VertexBuffer> Imp::VertexBuffer::Create(float* vertices, uint32_t const size)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}

Imp::Ref<Imp::IndexBuffer> Imp::IndexBuffer::Create(uint32_t* indices, uint32_t const count)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}

Imp::Ref<Imp::FrameBuffer> Imp::FrameBuffer::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>();
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}
