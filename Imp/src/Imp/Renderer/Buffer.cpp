#include "ImpPCH.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

Imp::VertexBuffer* Imp::VertexBuffer::Create(float* vertices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: IMP_ERROR("We do not support NONE as an API"); return nullptr;
	case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
	}

	IMP_WARNING("Unknown renderAPI type");

	return nullptr;
}

Imp::IndexBuffer* Imp::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: IMP_ERROR("We do not support NONE as an API"); return nullptr;
	case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
	}

	IMP_WARNING("Unknown renderAPI type");

	return nullptr;
}