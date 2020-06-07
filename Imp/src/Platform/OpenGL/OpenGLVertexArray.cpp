#include "ImpPCH.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Imp
{

	static GLenum GetShaderDataTypeToGLenum(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		IMP_ERROR("UNKNOWN SHADER DATA TYPE!");

		return 0;
	}
}

Imp::OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
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

void Imp::OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer)
{
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	uint32_t index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.GetComponentCount(),
			GetShaderDataTypeToGLenum(element.Type),
			element.Normalized,
			layout.GetStride(),
			(const void*)element.Offset);
		++index;
	}

	m_VertexBuffers.push_back(vertexBuffer);
}

void Imp::OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_pIndexBuffer = indexBuffer;
}
