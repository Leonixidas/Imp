#pragma once
#include "Imp/Renderer/Buffer.h"
#include "Imp/Renderer/Renderer.h"


namespace Imp
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetRendererID() { return mRendererID; }

		virtual void SetLayout(const BufferLayout& layout) override { mLayout = layout; }
		virtual const BufferLayout& GetLayout() const override { return mLayout; }
	private:
		BufferLayout mLayout;
		uint32_t mRendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override { return mCount; }
	private:
		uint32_t mRendererID;
		uint32_t mCount;
	};

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer();
		virtual ~OpenGLFrameBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void* GetFrame() const override;

	private:
		uint32_t mBufferID, mTextureID;
	};
}
