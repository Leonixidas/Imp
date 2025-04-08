#include "ImpPCH.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"


///////////////////////////////////////////////////////////////////////////
////////////////////  VERTEX BUFFER  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

Imp::OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
	IMP_PROFILE_FUNCTION();

	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

Imp::OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, uint32_t size)
{
	IMP_PROFILE_FUNCTION();
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

Imp::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	IMP_PROFILE_FUNCTION();
	glDeleteBuffers(1, &m_RendererID);
}

void Imp::OpenGLVertexBuffer::Bind() const
{
	IMP_PROFILE_FUNCTION();
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Imp::OpenGLVertexBuffer::UnBind() const
{
	IMP_PROFILE_FUNCTION();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Imp::OpenGLVertexBuffer::SetData(void const* data, uint32_t const size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

////////////////////////////////////////////////////////
//////////////////// INDEX BUFFER //////////////////////
////////////////////////////////////////////////////////

Imp::OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t const count)
	: m_Count(count)
{
	IMP_PROFILE_FUNCTION();
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(uint32_t) * count), indices, GL_STATIC_DRAW);
}

Imp::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	IMP_PROFILE_FUNCTION();
	glDeleteBuffers(1, &m_RendererID);
}

void Imp::OpenGLIndexBuffer::Bind() const
{
	IMP_PROFILE_FUNCTION();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Imp::OpenGLIndexBuffer::UnBind() const
{
	IMP_PROFILE_FUNCTION();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Imp::OpenGLFrameBuffer::OpenGLFrameBuffer(): m_TextureID(0)
{
	IMP_PROFILE_FUNCTION();
	glGenFramebuffers(1, &m_BufferID);
}

void Imp::OpenGLFrameBuffer::Bind() const
{
	IMP_PROFILE_FUNCTION();

}

void Imp::OpenGLFrameBuffer::UnBind() const
{
	IMP_PROFILE_FUNCTION();

}

uint32_t Imp::OpenGLFrameBuffer::GetFrame() const
{
	return m_TextureID;
}
