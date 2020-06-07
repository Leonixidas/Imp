#pragma once
#include "Imp/Renderer/RendererAPI.h"

namespace Imp
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(VertexArray* vertexArray) override;
	};
}

