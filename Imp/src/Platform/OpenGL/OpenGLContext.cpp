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
		IMP_INFO("Glad is initialized");
	else
	{
		IMP_ERROR("Glad was not initialized!");
#ifdef IMP_DEBUG
		__debugbreak();
#endif
	}
}

void Imp::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_pWindowHandle);
}
