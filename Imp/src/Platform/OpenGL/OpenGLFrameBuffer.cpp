#include "ImpPCH.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Imp
{
	static constexpr uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils
	{

		static GLenum TextureTarget(bool const multiSampled)
		{
			return multiSampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool const multiSampled, uint32_t* outId, uint32_t const count)
		{
			glCreateTextures(TextureTarget(multiSampled), count, outId);
		}

		static void BindTexture(bool const multiSampled, uint32_t const id)
		{
			glBindTexture(TextureTarget(multiSampled), id);
		}

		static void AttachColorTexture(uint32_t const id, int const samples, GLenum const internalFormat, GLenum const format, uint32_t const width, uint32_t const height, int const index)
		{
			bool const multiSampled = samples > 1;
			if (multiSampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, static_cast<int>(width), static_cast<int>(height), GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(internalFormat), static_cast<int>(width), static_cast<int>(height), 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multiSampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t const id, int const samples, GLenum const format, GLenum const attachmentType, uint32_t const width, uint32_t const height)
		{
			bool const multiSampled = samples > 1;
			if (multiSampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, static_cast<int>(width), static_cast<int>(height), GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, static_cast<int>(width), static_cast<int>(height));

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multiSampled), id, 0);
		}

		static bool IsDepthFormat(FrameBufferTextureFormat const format)
		{
			switch (format)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:  return true;
			case FrameBufferTextureFormat::None:
			case FrameBufferTextureFormat::RGBA8:
			case FrameBufferTextureFormat::RED_INTEGER:
				IMP_CORE_WARN("FrameBufferTextureFormat with id {0} has not been implemented yet!", static_cast<int>(format));
				break;
			}

			return false;
		}

		static GLenum ImpFBTextureFormatToGL(FrameBufferTextureFormat const format)
		{
			switch (format)
			{
			case FrameBufferTextureFormat::RGBA8:       return GL_RGBA8;
			case FrameBufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			case FrameBufferTextureFormat::None:
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				break;
			}

			IMP_CORE_ASSERT(false);
			return 0;
		}

	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferSpecification spec)
		: m_Specification(std::move(spec))
	{
		for (auto specification : m_Specification.Attachment.Attachments)
		{
			if (!Utils::IsDepthFormat(specification.TextureFormat))
				m_ColorAttachmentSpecifications.emplace_back(specification);
			else
				m_DepthAttachmentSpecification = specification;
		}

		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererId);
		glDeleteTextures(static_cast<GLsizei>(m_ColorAttachments.size()), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererId)
		{
			glDeleteFramebuffers(1, &m_RendererId);
			glDeleteTextures(static_cast<GLsizei>(m_ColorAttachments.size()), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_RendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererId);

		const bool multiSample = m_Specification.Samples > 1;

		// Attachments
		if (!m_ColorAttachmentSpecifications.empty())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multiSample, m_ColorAttachments.data(), static_cast<uint32_t>(m_ColorAttachments.size()));

			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(multiSample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
				case FrameBufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(m_ColorAttachments[i], static_cast<int>(m_Specification.Samples), GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, static_cast<int>(i));
					break;
				case FrameBufferTextureFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_ColorAttachments[i], static_cast<int>(m_Specification.Samples), GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, static_cast<int>(i));
					break;
				case FrameBufferTextureFormat::None:
				case FrameBufferTextureFormat::DEPTH24STENCIL8:
					IMP_CORE_WARN("FrameBufferTextureFormat with id {0} has not been implemented yet!", static_cast<int>(m_ColorAttachmentSpecifications[i].TextureFormat));
					break;
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FrameBufferTextureFormat::None)
		{
			Utils::CreateTextures(multiSample, &m_DepthAttachment, 1);
			Utils::BindTexture(multiSample, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				Utils::AttachDepthTexture(m_DepthAttachment, static_cast<int>(m_Specification.Samples), GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
				break;
			case FrameBufferTextureFormat::None:
			case FrameBufferTextureFormat::RGBA8:
			case FrameBufferTextureFormat::RED_INTEGER:
				IMP_CORE_WARN("FrameBufferTextureFormat with id {0} has not been implemented for Depth frame buffer yet!", static_cast<int>(m_DepthAttachmentSpecification.TextureFormat));
				break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			IMP_CORE_ASSERT(m_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(static_cast<int>(m_ColorAttachments.size()), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		IMP_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererId);
		glViewport(0, 0, static_cast<int>(m_Specification.Width), static_cast<int>(m_Specification.Height));
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			IMP_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;

		Invalidate();
	}

	int OpenGLFrameBuffer::ReadPixel(uint32_t const attachmentIndex, int const x, int const y)
	{
		IMP_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;

	}

	void OpenGLFrameBuffer::ClearAttachment(uint32_t const attachmentIndex, int const value)
	{
		IMP_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());

		auto& spec = m_ColorAttachmentSpecifications[attachmentIndex];
		glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
			Utils::ImpFBTextureFormatToGL(spec.TextureFormat), GL_INT, &value);
	}
}