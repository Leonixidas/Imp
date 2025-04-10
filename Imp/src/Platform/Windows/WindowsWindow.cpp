#include "ImpPCH.h"
#include "WindowsWindow.h"
#include "Imp/Events/ApplicationEvent.h"
#include "Imp/Events/KeyEvent.h"
#include "Imp/Events/MouseEvent.h"
#include "Imp/Core/Log.h"
#include "Imp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Imp
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int const error, char const* description)
	{
		IMP_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		IMP_PROFILE_FUNCTION();

		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		IMP_PROFILE_FUNCTION();
		WindowsWindow::ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		IMP_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		IMP_TRACE("Creating window: Initializing GLFW");

		if (s_GLFWWindowCount == 0)
		{
			IMP_PROFILE_SCOPE("glfwInit");
			bool succeed = glfwInit();
			IMP_CORE_ASSERT(succeed, "GLFW could not be initialized");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			IMP_PROFILE_SCOPE("glfwCreateWindow");
#if defined(IMP_DEBUG)
			if (Renderer::GetApi() == RendererApi::Api::OpenGl)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

			m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW callback functions for events
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData const& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				WindowCloseEvent e;
				data.Callback(e);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int x, int y)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.Width = x;
				data.Height = y;

				WindowResizeEvent e{ x, y };

				data.Callback(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData const& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e{ static_cast<MouseCode>(button), false };
					data.Callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e{ static_cast<MouseCode>(button) };

					data.Callback(e);
					break;
				}
				}
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData const& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent e{ static_cast<KeyCode>(key), false };
					data.Callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e{ static_cast<KeyCode>(key) };
					data.Callback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e{ static_cast<KeyCode>(key), true };
					data.Callback(e);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t key)
			{
				WindowData const& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				KeyTypedEvent e{ static_cast<KeyCode>(key) };
				data.Callback(e);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData const& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent e{ static_cast<float>(xOffset), static_cast<float>(yOffset) };

				data.Callback(e);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
			{
				WindowData const& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent e{ static_cast<float>(x), static_cast<float>(y) };

				data.Callback(e);
			});
	}

	uint32_t WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	uint32_t WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	void WindowsWindow::SetEventCallBack(const EventCallBack& callback)
	{
		m_Data.Callback = callback;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.Vsync;
	}

	void WindowsWindow::SetVSync(bool const vsync)
	{
		if (vsync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.Vsync = vsync;
	}

	void WindowsWindow::ShutDown()
	{
		IMP_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
			glfwTerminate();
	}
}