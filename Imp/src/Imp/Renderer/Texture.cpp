#include "ImpPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Imp
{
Ref<Texture2D> Texture2D::Create(const std::string& path)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}
Ref<FontTexture> FontTexture::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFontTexture>();
	default:
		IMP_CORE_ERROR("We do not support NONE as an API");
		return nullptr;
	}
}
}