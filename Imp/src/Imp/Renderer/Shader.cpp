#include "ImpPCH.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Imp/Log.h"


Imp::Ref<Imp::Shader> Imp::Shader::Create(const std::string& filePath)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: IMP_ERROR("NONE as API is not supported"); return nullptr;
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
	}

	IMP_ERROR("UNKNOWN RENDER API");
	return nullptr;
}

Imp::Ref<Imp::Shader> Imp::Shader::Create(const std::string& vertexSrc, const std::string& pixelSrc)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None: IMP_ERROR("NONE as API is not supported"); return nullptr;
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, pixelSrc);
	}

	IMP_ERROR("UNKNOWN RENDER API");
	return nullptr;
}