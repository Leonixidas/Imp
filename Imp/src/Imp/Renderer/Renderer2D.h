#pragma once
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "RendererApi.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "Imp/Core/Base.h"
#include "Imp/Scene/Component.h"

namespace Imp
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(Camera const& camera, glm::mat4 const& transform);
		static void BeginScene(PerspectiveCamera const& camera);
		static void BeginScene(OrthographicCamera const& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color);
		static void DrawQuad(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color);
		static void DrawQuad(glm::vec2 const& position, glm::vec2 const& size, Ref<Texture2D> const&, float tilingFactor = 1.f, glm::vec4 const& tintColor = glm::vec4(1.f));
		static void DrawQuad(glm::vec3 const& position, glm::vec2 const& size, Ref<Texture2D> const&, float tilingFactor = 1.f, glm::vec4 const& tintColor = glm::vec4(1.f));

		static void DrawQuad(glm::mat4 const& transform, glm::vec4 const& color, int entityId = -1);
		static void DrawQuad(glm::mat4 const& transform, Ref<Texture2D> const& texture, float tilingFactor = 1.f, glm::vec4 const& tintColor = glm::vec4(1.f), int entityId = -1);

		static void DrawRotatedQuad(glm::vec2 const& position, glm::vec2 const& size, float rotation, glm::vec4 const& color);
		static void DrawRotatedQuad(glm::vec3 const& position, glm::vec2 const& size, float rotation, glm::vec4 const& color);
		static void DrawRotatedQuad(glm::vec2 const& position, glm::vec2 const& size, float rotation, Ref<Texture2D> const& texture, float tilingFactor = 1.f, glm::vec4 const& tintColor = glm::vec4(1.f));
		static void DrawRotatedQuad(glm::vec3 const& position, glm::vec2 const& size, float rotation, Ref<Texture2D> const& texture, float tilingFactor = 1.f, glm::vec4 const& tintColor = glm::vec4(1.f));

		static void DrawCircle(glm::mat4 const& transform, glm::vec4 const& color, float radius = 1.f, int entityId = -1);

		static void DrawLine(glm::vec3 const& p0, glm::vec3 const& p1, glm::vec4 const& color, int entityId = -1);

		static void DrawRect(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color, int entityId = -1);
		static void DrawRect(glm::mat4 const& transform, glm::vec4 const& color, int entityId = -1);

		static void DrawSprite(glm::mat4 const& transform, SpriteRendererComponent& source, int entityId = -1);

		struct TextParams
		{
			glm::vec4 Color{ 1.f };
			float Kerning = 0.f;
			float LineSpacing = 0.f;
		};

		static void DrawString(std::string const& string, Ref<FontTexture> font, glm::mat4 const& tranaform, TextParams const& textParams, int entityId = -1);
		static void DrawString(std::string const& string, glm::mat4 const& transform, TextComponent const& component, int entityId = -1);

		static float GetLineWidth();
		static void SetLineWidth(float width);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void StartBatch();
		static void NextBatch();

		struct SceneData2D
		{
			Ref<OrthographicCamera> OrthoCamera;
			Ref<Shader> TextureShader;
			Ref<Shader> ColorShader;
			Ref<Shader> TextShader;
			Ref<Shader> TextureInstShader;
			Ref<VertexArray> NormalVertexArray;
			Ref<VertexArray> InstanceVertexArray;
			std::vector<Vertex> Vertices;
			Ref<FontTexture> Fonts;
		};

		static Scope<SceneData2D> m_Data2D;
	};
}
