#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include <map>
#include <unordered_map>

#include "OrthographicCamera.h"
#include "Vertex.h"

namespace Imp
{
	class Renderer
	{
	public:
		static void Init();
		static void ShutDown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera const& camera);
		static void EndScene();

		static void Submit(Ref<Shader> const& shader, Ref<VertexArray> const& vertexArray, glm::mat4 const& transform = glm::mat4(1.f));

		static uint32_t GetFrame();

		inline static RendererApi::Api GetApi() { return RendererApi::GetApi(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};


}
