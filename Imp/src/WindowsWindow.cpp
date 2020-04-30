#include "ImpPCH.h"
#include "WindowsWindow.h"
#include "Imp/Events/WindowEvent.h"
#include "Imp/Events/KeyEvent.h"
#include "Imp/Events/MouseEvent.h"
#include "Imp/Log.h"

#include "glad/glad.h"

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

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_pWindow);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.m_Title;
		m_Data.width = props.m_Width;
		m_Data.height = props.m_Height;

		Log::Succeed("Creating window: Initializing GLFW");

		if (!m_Initialized)
		{
			bool succeed = glfwInit();
			if (!succeed)
				Log::Error("GLFW could not be initialized");

			m_Initialized = true;
		}

		m_pWindow = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_pWindow);

		// INITIALIZING GLAD
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status > 0)
			Log::Info("Glad is initialized");
		else
		{
			Log::Error("Glad was not initialized!");
			return;
		}

		glfwSetWindowUserPointer(m_pWindow, &m_Data);
		SetVSync(true);

		//Set GLFW callback functions for events
		glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.callback(e);
		});

		glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* window, int x, int y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = x;
			data.height = y;

			WindowResizeEvent e{ float(x), float(y) };
			
			data.callback(e);
		});

		glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e{ button,false };
				data.callback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e{ button };

				data.callback(e);
				break;
			}
			}
		});

		glfwSetKeyCallback(m_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent e{ key, false };
				data.callback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent e{ key };
				data.callback(e);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent e{ key, true };
				data.callback(e);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_pWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e{ float(xOffset) };

			data.callback(e);
		});

		glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e{ int(x), int(y) };

			data.callback(e);
		});
	}

	unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data.width;
	}

	unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data.height;
	}

	void WindowsWindow::SetEventCallBack(const EventCallBack& callback)
	{
		m_Data.callback = callback;
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

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
	}
}