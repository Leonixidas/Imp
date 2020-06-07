#pragma once
#include "RenderCommand.h"

namespace Imp
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(VertexArray* vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}