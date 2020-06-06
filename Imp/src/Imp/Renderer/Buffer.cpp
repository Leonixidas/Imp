#include "ImpPCH.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Imp/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

Imp::VertexBuffer* Imp::VertexBuffer::Create(float* vertices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::NONE: IMP_ERROR("We do not support NONE as an API"); return nullptr;
	case RenderAPI::OPENGL: return new OpenGLVertexBuffer(vertices, size);
	}

	IMP_WARNING("Unknown renderAPI type");

	return nullptr;
}

Imp::IndexBuffer* Imp::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::NONE: IMP_ERROR("We do not support NONE as an API"); return nullptr;
	case RenderAPI::OPENGL: return new OpenGLIndexBuffer(indices, count);
	}

	IMP_WARNING("Unknown renderAPI type");

	return nullptr;
}