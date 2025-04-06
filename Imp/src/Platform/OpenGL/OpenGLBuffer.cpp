#include "ImpPCH.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"


///////////////////////////////////////////////////////////////////////////
////////////////////  VERTEX BUFFER  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

Imp::OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

Imp::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Imp::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Imp::OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

////////////////////////////////////////////////////////
//////////////////// INDEX BUFFER //////////////////////
////////////////////////////////////////////////////////

Imp::OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t const count)
	: m_Count(count)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(uint32_t) * count), indices, GL_STATIC_DRAW);
}

Imp::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Imp::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Imp::OpenGLIndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Imp::OpenGLFrameBuffer::OpenGLFrameBuffer(): m_TextureID(0)
{
	glGenFramebuffers(1, &m_BufferID);
}

void Imp::OpenGLFrameBuffer::Bind() const
{

}

void Imp::OpenGLFrameBuffer::UnBind() const
{

}

uint32_t Imp::OpenGLFrameBuffer::GetFrame() const
{
	return m_TextureID;
}
