#pragma once

#include "Imp/Renderer/FrameBuffer.h"

namespace Imp
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(FrameBufferSpecification spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual uint32_t GetColorAttachmentRendererId(uint32_t index) const override { IMP_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }

		virtual  FrameBufferSpecification const& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererId = 0;
		FrameBufferSpecification m_Specification;

		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentSpecification = FrameBufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}