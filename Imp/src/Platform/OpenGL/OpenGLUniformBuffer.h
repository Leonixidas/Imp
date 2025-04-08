#pragma once

#include "Imp/Renderer/UniformBuffer.h"

namespace Imp
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t binding);
		virtual ~OpenGLUniformBuffer();

		virtual void SetData(void const* data, uint32_t size, uint32_t offset) override;
	private:
		uint32_t m_RendererId = 0;
	};
}