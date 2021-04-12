#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include <map>
#include <unordered_map>

namespace Imp
{
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(const Ref<Camera>& pCam);
		static void EndScene();

		static void Submit(const Ref<Shader>& pShader, const Ref<VertexArray>& pVertexArray);

		static void* GetFrame();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:
		struct SceneData
		{
			Ref<Camera> pCamera = nullptr;
		};

		static Scope<SceneData> m_pSceneData;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(const Ref<OrthographicCamera>& pCam);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& pVertexArray, const Ref<Texture2D>& texture, const glm::mat4& world);

		//initial size of the quad is 1 unit this means that the size of the quad is equal to the scale of the object
		//texture coordinates are defined by 4 floats left/right/bottom/top
		static void DrawQuadTexture(const Ref<Texture2D>& pTexture, const glm::mat4& world, const glm::vec4& texCoords = { 0.f,1.f,0.f,1.f });
		static void DrawQuadFlatColor(const glm::vec4& color, const glm::mat4& world);
		static void DrawQuadFlatColor(const glm::vec4& color);

		static void DrawQuadInstanced(const Ref<Texture2D>& pTexture, const std::vector<glm::mat4>& matrices, const glm::vec4& texCoords = { 0.f,1.f,0.f,1.f });
		static void CreateInstancedBuffer(std::vector<glm::mat4>& matrices);
		static void SubmitInstancedBufferData(std::vector<glm::mat4>& world);
		static void SubmitBufferData(const glm::vec4& uvs);
		static void SubmitBufferData(const std::vector<glm::vec2>& vertices);

		//Note that the size of the characters will depend on the loaded file
		static void DrawString(const std::string& fontName, const std::string& text, const glm::mat4& world, const glm::vec4& color = { 1,1,1,1 });

		static void LoadFont(const std::string& filepath);

		static bool HasFont(const std::string& fontname);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static void SetUVsAndDefaultPos(const glm::vec4& uv);
		static void SetVertices(const std::vector<glm::vec2>& vertices);

		struct SceneData2D
		{
			Ref<OrthographicCamera> m_pOrthoCamera;
			Ref<Shader> m_pTextureShader;
			Ref<Shader> m_pColorShader;
			Ref<Shader> m_pTextShader;
			Ref<Shader> m_pTextureInstShader;
			Ref<VertexArray> m_pVertexArray;
			Ref<VertexArray> m_pInstanceVertexArray;
			std::vector<Vertex> m_Vertices;
			Ref<FontTexture> m_pFonts;
		};

		static Scope<SceneData2D> m_p2DData;
	};
}