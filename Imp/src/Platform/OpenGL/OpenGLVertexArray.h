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

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) override;

		virtual IndexBuffer* GetIndexBuffer() const override  { return m_pIndexBuffer; };

	private:
		uint32_t m_RendererID;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_pIndexBuffer = nullptr;
	};
}