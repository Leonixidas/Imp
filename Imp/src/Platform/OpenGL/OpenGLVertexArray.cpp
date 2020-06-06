#include "ImpPCH.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"


Imp::OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

Imp::OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void Imp::OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void Imp::OpenGLVertexArray::UnBind() const
{
	glBindVertexArray(0);
}
