#include "ImpPCH.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"


///////////////////////////////////////////////////////////////////////////
////////////////////VERTEXBUFFER///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

Imp::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &mRendererID);
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

Imp::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &mRendererID);
}

void Imp::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void Imp::OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

///////////////////////////////////////////////////////////////////////////
////////////////////INDEXBUFFER////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

Imp::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	: mCount(count)
{
	glCreateBuffers(1, &mRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Imp::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &mRendererID);
}

void Imp::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void Imp::OpenGLIndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Imp::OpenGLFrameBuffer::OpenGLFrameBuffer()
	: mTextureID()
{
	glGenFramebuffers(1, &mBufferID);
	
}

Imp::OpenGLFrameBuffer::~OpenGLFrameBuffer()
{

}

void Imp::OpenGLFrameBuffer::Bind() const
{

}

void Imp::OpenGLFrameBuffer::UnBind() const
{

}

void* Imp::OpenGLFrameBuffer::GetFrame() const
{
	return (void*)(&mTextureID);
}
