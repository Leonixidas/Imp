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
		TextureManager() {}
		~TextureManager() = default;

		void AddTexture(const Ref<Texture2D>& tex, const std::string& name = "Texture");
		void DeleteTexture(const std::string& name);

		Ref<Texture2D>& GetTexture(const std::string& name);

	private:
		std::unordered_map<std::string, Texture2D> mTextures;
	};
}