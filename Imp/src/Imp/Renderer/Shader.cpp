#include "ImpPCH.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Imp/Log.h"


Imp::Ref<Imp::Shader> Imp::Shader::Create(std::string const& filePath)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
	default:
		IMP_CORE_FATAL("API with id: {0} is not supported!", Renderer::GetAPI());
		return nullptr;

	}
}

Imp::Ref<Imp::Shader> Imp::Shader::Create(std::string const& vertexSrc, std::string const& pixelSrc)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, pixelSrc);
	default:
		IMP_CORE_FATAL("API with id: {0} is not supported!", Renderer::GetAPI());
		return nullptr;
	}
}