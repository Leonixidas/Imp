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

void Imp::OpenGLVertexArray::SubmitBufferData(uint32_t bufferSlot, float* vertices, uint32_t size)
{
	glBindVertexArray(m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[bufferSlot]->GetRendererID());
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}

void Imp::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	uint32_t index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.GetComponentCount(),
			GetShaderDataTypeToGLenum(element.Type),
			element.Normalized,
			layout.GetStride(),
			(const void*)size_t(element.Offset));
		++index;
	}

	m_VertexBuffers.push_back(vertexBuffer);
}

void Imp::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_pIndexBuffer = indexBuffer;
}

//for matrices
void Imp::OpenGLVertexArray::AddInstancedBuffer(const Ref<VertexBuffer>& vertexBuffer, uint32_t attribLocation)
{
	uint32_t pos1 = attribLocation;
	uint32_t pos2 = pos1 + 1;
	uint32_t pos3 = pos2 + 1;
	uint32_t pos4 = pos3 + 1;

	vertexBuffer->Bind();
	auto& layout = vertexBuffer->GetLayout();

	for (auto& element : layout)
	{
		glEnableVertexAttribArray(pos1);
		glEnableVertexAttribArray(pos2);
		glEnableVertexAttribArray(pos3);
		glEnableVertexAttribArray(pos4);

		glVertexAttribPointer(pos1, 4, GetShaderDataTypeToGLenum(element.Type), element.Normalized, layout.GetStride(), (void*)(0));
		glVertexAttribPointer(pos2, 4, GetShaderDataTypeToGLenum(element.Type), element.Normalized, layout.GetStride(), (void*)(sizeof(float) * 4));
		glVertexAttribPointer(pos3, 4, GetShaderDataTypeToGLenum(element.Type), element.Normalized, layout.GetStride(), (void*)(sizeof(float) * 8));
		glVertexAttribPointer(pos4, 4, GetShaderDataTypeToGLenum(element.Type), element.Normalized, layout.GetStride(), (void*)(sizeof(float) * 12));

		glVertexAttribDivisor(pos1, 1);
		glVertexAttribDivisor(pos1, 2);
		glVertexAttribDivisor(pos1, 3);
		glVertexAttribDivisor(pos1, 4);
	}

	m_VertexBuffers.push_back(vertexBuffer);
}
