#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Imp
{
	class RendererApi
	{
	public:
		enum class Api
		{
			None = 0, OpenGl
		};

		virtual ~RendererApi() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(glm::vec4 const& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(Ref<VertexArray> const& vertexArray, uint32_t indexCount = 0) = 0;

		virtual void DrawInstanced(Ref<VertexArray> const& vertexArray, uint32_t instanceCount) = 0;

		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

		virtual void SetLineWidth(float width) = 0;

		virtual uint32_t GetFrameId() = 0;

		inline static Api GetApi() { return s_Api; }


		static Scope<RendererApi> Create();

	private:
		static Api s_Api;
	};
}
