#include "ImpPCH.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

/////////////////////////////////////////////
/////////////  SHADER PROPS  ////////////////
/////////////////////////////////////////////

Imp::ShaderProps::ShaderProps(std::vector<ShaderDataType> const& props)
{
	for (ShaderDataType const& d : props)
	{
		m_BufferSize += GetShaderDataTypeSize(d);
	}

	m_Buffer = new char[m_BufferSize];
}

Imp::ShaderProps::~ShaderProps()
{
	delete[] m_Buffer;
	m_Buffer = nullptr;
}

void Imp::ShaderProps::SetShaderProperty(uint32_t const index, char const* data, ShaderDataType const type) const
{
	uint32_t size = GetShaderDataTypeSize(type);

	if (index + size >= m_BufferSize)
	{
		IMP_CORE_ERROR("Shader data type doesn't fit in buffer starting at given index");
		return;
	}

	for (uint32_t i = 0; i < size; ++i)
	{
		m_Buffer[index] = data[i];
	}
}

template <typename T>
T* Imp::ShaderProps::GetShaderProperty(uint32_t const index)
{
	if (index + sizeof(T) >= m_BufferSize)
	{
		IMP_CORE_ERROR("The size of the given type doesn't fit in the buffer at the given index");
		return nullptr;
	}

	return static_cast<T*>(&m_Buffer[index]);
}



/////////////////////////////////////////////
///////////// Vertex Buffer  ////////////////
/////////////////////////////////////////////
Imp::Ref<Imp::VertexBuffer> Imp::VertexBuffer::Create(uint32_t const size)
{
	switch (Renderer::GetApi())
	{
	case RendererApi::Api::OpenGl: return std::make_shared<OpenGLVertexBuffer>(size);
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}

Imp::Ref<Imp::VertexBuffer> Imp::VertexBuffer::Create(float* vertices, uint32_t const size)
{
	switch (Renderer::GetApi())
	{
	case RendererApi::Api::OpenGl: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}

////////////////////////////////////////////
///////////// Index Buffer  ////////////////
////////////////////////////////////////////

Imp::Ref<Imp::IndexBuffer> Imp::IndexBuffer::Create(uint32_t* indices, uint32_t const count)
{
	switch (Renderer::GetApi())
	{
	case RendererApi::Api::OpenGl: return std::make_shared<OpenGLIndexBuffer>(indices, count);
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}

////////////////////////////////////////////
///////////// Frame Buffer  ////////////////
/////////////////////////////////////////////

Imp::Ref<Imp::FrameBuffer> Imp::FrameBuffer::Create()
{
	switch (Renderer::GetApi())
	{
	case RendererApi::Api::OpenGl: return std::make_shared<OpenGLFrameBuffer>();
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}
