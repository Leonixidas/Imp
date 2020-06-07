#pragma once
#include "Buffer.h"

namespace Imp
{
	class VertexArray
	{
	public:
		virtual ~VertexArray(){}
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;

		virtual IndexBuffer* GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}