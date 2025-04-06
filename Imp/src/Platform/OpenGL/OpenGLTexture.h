#pragma once
#include "Imp/Renderer/Texture.h"

namespace Imp
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(std::string const& path);

		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }

		virtual void Bind(uint32_t slot = 0);

	private:
		std::string ath;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};

	class OpenGLFontTexture : public FontTexture
	{
	public:
		OpenGLFontTexture() {}
		virtual ~OpenGLFontTexture();

		virtual void Bind(std::string const& fontName) override;
		virtual std::unordered_map<char, Character>& GetFontCharacters(std::string const& fontName) override { return m_FontCharacters[fontName]; }
		virtual Ref<Texture2D> GetFontTexture(std::string const& fontName) { return m_FontTextures[fontName]; }

		virtual bool HasTexture(std::string const& fontName) override;

		virtual void LoadFont(std::string const& filepath) override;

	private:
		std::string ReadFile(std::string const& filePath);

		std::unordered_map<std::string, std::unordered_map<char, Character>> m_FontCharacters;
		std::unordered_map<std::string, Ref<Texture2D>> m_FontTextures;

	};
}