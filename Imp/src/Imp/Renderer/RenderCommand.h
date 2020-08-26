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
		inline static void SetClearColor(const glm::vec4& color)
		{
			m_pRendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			m_pRendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			m_pRendererAPI->DrawIndexed(vertexArray);
		}

		inline static void DrawInstanced(const Ref<VertexArray>& vertexArray, uint32_t instanceCount)
		{
			m_pRendererAPI->DrawInstanced(vertexArray, instanceCount);
		}

	private:
		static Scope<RendererAPI> m_pRendererAPI;
	};
}