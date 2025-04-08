#pragma once
#include "Imp/Renderer/RendererApi.h"

namespace Imp
{
	class OpenGLRendererAPI : public RendererApi
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

		virtual void DrawInstanced(const Ref<VertexArray>& vertexArray, uint32_t instanceCount) override;

		virtual uint32_t GetFrameId() override;

		void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;
		void SetLineWidth(float width) override;

	private:
		uint32_t m_FrameID = 0;
	};
}

