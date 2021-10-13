#pragma once
#include "RendererAPI.h"

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

	inline static void* GetFrame()
	{
		return m_pRendererAPI->GetFrame();
	}

private:
	static Scope<RendererAPI> m_pRendererAPI;
};
}