#pragma once
#include "Imp/Core.h"
#include <string>
#include <glm/glm.hpp>

namespace Imp
{
	struct Character
	{
		glm::vec4 uv;
		glm::vec2 Size;
		glm::vec2 Offset;
		float AdvanceX;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};

	class FontTexture
	{
	public:
		virtual ~FontTexture() = default;
		
		virtual void LoadFont(const std::string& filepath) = 0;
		virtual void Bind(const std::string& fontName) = 0;

		virtual std::unordered_map<char, Character>& GetFontCharacters(const std::string& fontName) = 0;
		virtual Ref<Texture2D> GetFontTexture(const std::string& fontName) = 0;

		virtual bool HasTexture(const std::string& fontName) = 0;

		static Ref<FontTexture> Create();

	};
}