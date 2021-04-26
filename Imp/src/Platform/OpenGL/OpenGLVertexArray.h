#pragma once
#include "Imp/Renderer/VertexArray.h"

namespace Imp
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SubmitBufferData(uint32_t bufferSlot, float* vertices, uint32_t size) override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual Ref<IndexBuffer> GetIndexBuffer() const override  { return mpIndexBuffer; };

		virtual void AddInstancedBuffer(const Ref<VertexBuffer>& vertexBuffer, uint32_t attribLocation) override;

	private:
		uint32_t mRendererID;
		std::vector<Ref<VertexBuffer>> mVertexBuffers;
		Ref<IndexBuffer> mpIndexBuffer = nullptr;
	};
}