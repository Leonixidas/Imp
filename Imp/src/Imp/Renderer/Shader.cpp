#include "ImpPCH.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Imp/Log.h"


Imp::Ref<Imp::Shader> Imp::Shader::Create(std::string const& filePath)
{
	switch (Renderer::GetApi())
	{
	case RendererApi::Api::OpenGl: return std::make_shared<OpenGLShader>(filePath);
	default:
		IMP_CORE_FATAL("API with id: {0} is not supported!", static_cast<int>(Renderer::GetApi()));
		return nullptr;

	}
}

Imp::Ref<Imp::Shader> Imp::Shader::Create(std::string const& vertexSrc, std::string const& pixelSrc)
{
	switch (Renderer::GetApi())
	{
	case RendererApi::Api::OpenGl: return std::make_shared<OpenGLShader>(vertexSrc, pixelSrc);
	default:
		IMP_CORE_FATAL("API with id: {0} is not supported!", static_cast<int>(RendererApi::GetApi()));
		return nullptr;
	}
}