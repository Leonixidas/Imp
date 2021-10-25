#include "ImpPCH.h"
#include "OpenGLContext.h"
#include "Glad/glad.h"
#include "Imp/Log.h"

Imp::OpenGLContext::OpenGLContext(GLFWwindow* window)
	: m_pWindowHandle(window)
{

}

void Imp::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_pWindowHandle);
	// INITIALIZING GLAD
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status > 0)
	{
		IMP_CORE_TRACE("Glad is initialized");
	}
	else
	{
		IMP_CORE_FATAL("Glad was not initialized! Exited with id = {0}", status);
#ifdef IMP_DEBUG
		__debugbreak();
#endif
	}
}

void Imp::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_pWindowHandle);
}
