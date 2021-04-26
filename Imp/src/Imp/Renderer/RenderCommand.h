#pragma once
#include "RendererAPI.h"

namespace Imp
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			mpRendererAPI->Init();
		}
		inline static void SetClearColor(const glm::vec4& color)
		{
			mpRendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			mpRendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			mpRendererAPI->DrawIndexed(vertexArray);
		}

		inline static void DrawInstanced(const Ref<VertexArray>& vertexArray, uint32_t instanceCount)
		{
			mpRendererAPI->DrawInstanced(vertexArray, instanceCount);
		}

		inline static void* GetFrame()
		{
			return mpRendererAPI->GetFrame();
		}

	private:
		static Scope<RendererAPI> mpRendererAPI;
	};
}