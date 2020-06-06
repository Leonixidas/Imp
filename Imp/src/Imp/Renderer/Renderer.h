#pragma once

namespace Imp
{
	enum class RenderAPI
	{
		NONE = 0, OPENGL = 1
	};

	class Renderer
	{
	public:
		inline static RenderAPI GetAPI() { return m_RenderAPI; }
	private:
		static RenderAPI m_RenderAPI;
	};
}