#include "ImpPCH.h"
#include "WindowsWindow.h"
#include "Imp/Log.h"

namespace Imp
{
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data.width;
	}
	unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data.height;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.vsync;
	}
	void WindowsWindow::SetVSync(bool vsync)
	{
		if (vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.vsync = vsync;
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_pWindow);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.m_Title;
		m_Data.width = props.m_Width;
		m_Data.height = props.m_Height;

		Log::Info("Creating window: Initializing GLFW");

		if (!m_Initialized)
		{
			bool succeed = glfwInit();
			if (!succeed)
				Log::Error("GLFW could not be initialized");

			m_Initialized = true;
		}

		m_pWindow = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_pWindow);
		glfwSetWindowUserPointer(m_pWindow, &m_Data);
		SetVSync(true);
	}
	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_pWindow);
	}
}