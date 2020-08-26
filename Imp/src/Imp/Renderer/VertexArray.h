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

		virtual void SubmitBufferData(uint32_t bufferSlot, float* vertices, uint32_t size) = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual void AddInstancedBuffer(const Ref<VertexBuffer>& vertexBuffer, uint32_t attribLocation) = 0;

		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}