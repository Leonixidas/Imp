#pragma once
#include "RendererAPI.h"

namespace Imp
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			m_pRendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			m_pRendererAPI->Clear();
		}

		inline static void DrawIndexed(VertexArray* vertexArray)
		{
			m_pRendererAPI->DrawIndexed(vertexArray);
		}

		static void ShutDown() { delete m_pRendererAPI; }

	private:
		static RendererAPI* m_pRendererAPI;
	};
}