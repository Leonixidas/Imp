#pragma once
#include "Imp/Renderer/Texture.h"

namespace Imp
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);

		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }

		virtual void Bind(uint32_t slot = 0);

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};

	class OpenGLFontTexture : public FontTexture
	{
	public:
		OpenGLFontTexture() {}
		virtual ~OpenGLFontTexture();

		virtual void Bind(const std::string& fontName) override;
		virtual std::unordered_map<char, Character>& GetFontCharacters(const std::string& fontName) override { return m_FontCharacters[fontName]; }
		virtual Ref<Texture2D> GetFontTexture(const std::string& fontName) { return m_FontTextures[fontName]; }

		virtual bool HasTexture(const std::string& fontName) override;

		virtual void LoadFont(const std::string& filepath) override;

	private:
		std::string ReadFile(const std::string& filePath);

		std::unordered_map<std::string, std::unordered_map<char, Character>> m_FontCharacters;
		std::unordered_map<std::string, Ref<Texture2D>> m_FontTextures;

	};
}