#pragma once
#include "Imp/Renderer/Texture.h"

namespace Imp
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);

		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const { return mWidth; }
		virtual uint32_t GetHeight() const { return mHeight; }

		virtual void Bind(uint32_t slot = 0);

	private:
		std::string mPath;
		uint32_t mWidth, mHeight;
		uint32_t mRendererID;
	};

	class OpenGLFontTexture : public FontTexture
	{
	public:
		OpenGLFontTexture() {}
		virtual ~OpenGLFontTexture();

		virtual void Bind(const std::string& fontName) override;
		virtual std::unordered_map<char, Character>& GetFontCharacters(const std::string& fontName) override { return mFontCharacters[fontName]; }
		virtual Ref<Texture2D> GetFontTexture(const std::string& fontName) { return mFontTextures[fontName]; }

		virtual bool HasTexture(const std::string& fontName) override;

		virtual void LoadFont(const std::string& filepath) override;

	private:
		std::string ReadFile(const std::string& filePath);

		std::unordered_map<std::string, std::unordered_map<char, Character>> mFontCharacters;
		std::unordered_map<std::string, Ref<Texture2D>> mFontTextures;

	};
}