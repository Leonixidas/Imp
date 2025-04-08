#pragma once
#include "RendererApi.h"

namespace Imp
{
class RenderCommand
{
public:
	inline static void Init()
	{
		s_RendererAPI->Init();
	}

	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	inline static void SetClearColor(glm::vec4 const& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	inline static void Clear()
	{
		s_RendererAPI->Clear();
	}

	inline static void DrawIndexed(Ref<VertexArray> const& vertexArray, uint32_t indexCount = 0)
	{
		s_RendererAPI->DrawIndexed(vertexArray, indexCount);
	}

	inline static void DrawLines(Ref<VertexArray> const& vertexArray, uint32_t vertexCount)
	{
		s_RendererAPI->DrawLines(vertexArray, vertexCount);
	}

	inline static void DrawInstanced(Ref<VertexArray> const& vertexArray, uint32_t const instanceCount)
	{
		s_RendererAPI->DrawInstanced(vertexArray, instanceCount);
	}

	inline static uint32_t GetFrame()
	{
		return s_RendererAPI->GetFrameId();
	}

private:
	static Scope<RendererApi> s_RendererAPI;
};
}