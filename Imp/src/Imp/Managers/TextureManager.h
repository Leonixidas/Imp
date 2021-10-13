#pragma once
#include "Imp/Core.h"
#include "Imp/Singleton.h"
#include "Imp/Renderer/Texture.h"
#include <unordered_map>

namespace Imp
{
class TextureManager : public Singleton<TextureManager>
{
public:
	TextureManager() = default;
	~TextureManager() = default;

	void AddTexture(Ref<Texture2D> const& tex, std::string const& name = "Texture");
	void DeleteTexture(std::string const& name);

	Ref<Texture2D>& GetTexture(std::string const& name);

private:
	std::unordered_map<std::string, Texture2D> m_Textures;
};
}