#include "ImpPCH.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Imp/Log.h"


Imp::Shader* Imp::Shader::Create(const std::string& vertexSrc, const std::string& pixelSrc)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::NONE: IMP_ERROR("NONE as API is not supported"); return nullptr;
	case RenderAPI::OPENGL: return new OpenGLShader(vertexSrc, pixelSrc);
	}

	IMP_ERROR("UNKNOWN RENDER API");
	return nullptr;
}