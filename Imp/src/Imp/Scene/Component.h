#pragma once
#include "glm/glm.hpp"
#include "Imp/Core/Base.h"
#include "Imp/Renderer/Texture.h"

namespace Imp
{
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color)
		{
		}
	};

	struct RenderComponent
	{
	public:
		RenderComponent() = default;
		RenderComponent(const RenderComponent&) = default;
		RenderComponent(uint8_t meshId, uint8_t materialId)
			: MeshId(meshId)
			, MaterialId(materialId)
		{
		}

	private:
		uint8_t MeshId, MaterialId;
	};

	struct TextComponent
	{
		std::string TextString;
		Ref<FontTexture> FontAsset = FontTexture::Create();
		glm::vec4 Color{ 1.0f };
		float Kerning = 0.0f;
		float LineSpacing = 0.0f;
	};
}
