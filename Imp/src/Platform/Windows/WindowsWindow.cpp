#include "ImpPCH.h"
#include "WindowsWindow.h"
#include "Imp/Events/WindowEvent.h"
#include "Imp/Events/KeyEvent.h"
#include "Imp/Events/MouseEvent.h"
#include "Imp/Log.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "glad/glad.h"

namespace Imp
{
Ref<Window> Window::Create(const WindowProps& props)
{
	return std::make_shared<WindowsWindow>(props);
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
	m_pContext->SwapBuffers();
}

void WindowsWindow::Init(const WindowProps& props)
{
	m_Data.title = props.m_Title;
	m_Data.width = props.m_Width;
	m_Data.height = props.m_Height;

	IMP_TRACE("Creating window: Initializing GLFW");

	if (!m_Initialized)
	{
		bool succeed = glfwInit();
		if (!succeed)
		{
			IMP_CORE_ERROR("GLFW could not be initialized");
		}
		m_Initialized = true;
	}


	m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
	m_pContext = Ref<GraphicsContext>(new OpenGLContext(m_Window));

	m_pContext->Init();

	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	//Set GLFW callback functions for events
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow * window)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent e;
		data.callback(e);
	});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow * window, int x, int y)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = x;
		data.height = y;

		WindowResizeEvent e{ x, y };

		data.callback(e);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow * window, int button, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent e{ static_cast<MouseCode>(button), false };
			data.callback(e);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent e{ static_cast<MouseCode>(button) };

			data.callback(e);
			break;
		}
		}
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent e{ static_cast<KeyCode>(key), false };
			data.callback(e);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent e{ static_cast<KeyCode>(key) };
			data.callback(e);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent e{ static_cast<KeyCode>(key), true };
			data.callback(e);
			break;
		}
		}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow * window, uint32_t key)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		KeyTypedEvent e{ static_cast<KeyCode>(key) };
		data.callback(e);
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow * window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent e{ (float)xOffset, (float)yOffset };

		data.callback(e);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow * window, double x, double y)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent e{ (float)x, (float)y };

		data.callback(e);
	});
}

uint32_t WindowsWindow::GetWidth() const
{
	return m_Data.width;
}

uint32_t WindowsWindow::GetHeight() const
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
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}

	m_Data.vsync = vsync;
}

void WindowsWindow::ShutDown()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
}