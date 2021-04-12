#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Imp
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL
		};
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		virtual void DrawInstanced(const Ref<VertexArray>& vertexArray, uint32_t instanceCount) = 0;

		virtual void* GetFrame() = 0;

		inline static API GetAPI() { return m_API; }

	private:
		static API m_API;
	};
}
