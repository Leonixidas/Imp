#pragma once
#include "Glad/glad.h"
#include "Imp/Renderer/Texture.h"

namespace Imp
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(std::string const& path);
		OpenGLTexture2D(TextureSpecification const& specification);

		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetRendererId() const override { return m_RendererId; }	
		std::string const& GetPath() const override { return m_Path; }

		virtual void Bind(uint32_t slot = 0) override;

		TextureSpecification const& GetSpecification() const override { return m_Specification; }

		void SetData(void* data, uint32_t size) override;

		bool IsLoaded() const override { return m_IsLoaded; }

		bool operator==(const Texture& other) const override
		{
			return m_RendererId == other.GetRendererId();
		}

	private:
		TextureSpecification m_Specification;

		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererId;
		bool m_IsLoaded = false;
		GLenum m_InternalFormat, m_DataFormat;
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