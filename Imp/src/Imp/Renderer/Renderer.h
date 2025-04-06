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
	static void BeginScene(const Ref<Camera>& pCam);
	static void EndScene();

	static void OnWindowResize(uint32_t width, uint32_t height);

	static void Submit(const Ref<Shader>& pShader, const Ref<VertexArray>& pVertexArray);

	static uint32_t GetFrame();

	inline static RendererApi::Api GetApi() { return RendererApi::GetApi(); }


private:
	struct SceneData
	{
		Ref<Camera> Camera = nullptr;
	};

	static Scope<SceneData> m_SceneData;
};


}
