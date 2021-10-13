#include "ImpPCH.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Imp/Log.h"


Imp::Ref<Imp::Shader> Imp::Shader::Create(std::string const& filePath)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: IMP_ERROR("NONE as API is not supported"); return nullptr;
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
	}

	IMP_ERROR("UNKNOWN RENDER API");
	return nullptr;
}

Imp::Ref<Imp::Shader> Imp::Shader::Create(std::string const& vertexSrc, std::string const& pixelSrc)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: IMP_ERROR("NONE as API is not supported"); return nullptr;
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, pixelSrc);
	}

	IMP_ERROR("UNKNOWN RENDER API");
	return nullptr;
}