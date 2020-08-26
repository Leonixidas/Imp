#pragma once
#include "imp/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Imp
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_pWindowHandle;
	};
}