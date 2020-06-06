#pragma once

#include "Imp/Renderer/Shader.h"

namespace Imp
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& pixelSrc);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void UnBind() const override;

	private:
		uint32_t m_RendererID;
	};
}