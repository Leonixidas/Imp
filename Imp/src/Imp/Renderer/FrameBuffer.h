#pragma once

namespace Imp
{
	enum class FrameBufferTextureFormat
	{
		None = 0,
		RGBA8,
		RED_INTEGER,
		DEPTH24STENCIL8,
		Depth = DEPTH24STENCIL8
	};

	struct FrameBufferTextureSpecification
	{
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format) : TextureFormat(format) {}

		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
	};

	struct FrameBufferAttachmentSpecification
	{
		FrameBufferAttachmentSpecification() = default;
		FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> const attachments) : Attachments(attachments) {}

		std::vector<FrameBufferTextureSpecification> Attachments;
	};

	struct FrameBufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		FrameBufferAttachmentSpecification Attachment;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual uint32_t GetColorAttachmentRendererId(uint32_t index = 0) const = 0;

		virtual FrameBufferSpecification const& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(FrameBufferSpecification const& spec);
	};
}