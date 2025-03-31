#pragma once
#include "RendererApi.h"

namespace Imp
{
class RenderCommand
{
public:
	inline static void Init()
	{
		m_pRendererAPI->Init();
	}
	inline static void SetClearColor(glm::vec4 const& color)
	{
		m_pRendererAPI->SetClearColor(color);
	}

	inline static void Clear()
	{
		m_pRendererAPI->Clear();
	}

	inline static void DrawIndexed(Ref<VertexArray> const& vertexArray)
	{
		m_pRendererAPI->DrawIndexed(vertexArray);
	}

	inline static void DrawInstanced(Ref<VertexArray> const& vertexArray, uint32_t const instanceCount)
	{
		m_pRendererAPI->DrawInstanced(vertexArray, instanceCount);
	}

	inline static uint32_t GetFrame()
	{
		return m_pRendererAPI->GetFrameId();
	}

private:
	static Scope<RendererApi> m_pRendererAPI;
};
}