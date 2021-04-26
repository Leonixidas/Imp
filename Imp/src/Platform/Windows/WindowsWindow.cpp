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
		mpContext->SwapBuffers();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		mData.title = props.mTitle;
		mData.width = props.mWidth;
		mData.height = props.mHeight;

		IMP_SUCCEED("Creating window: Initializing GLFW");


		if (!mInitialized)
		{
			bool succeed = glfwInit();
			if (!succeed)
			{
				IMP_ERROR("GLFW could not be initialized");
			}
			mInitialized = true;
		}


		mpWindow = glfwCreateWindow(mData.width, mData.height, mData.title.c_str(), nullptr, nullptr);
		mpContext = Ref<GraphicsContext>(new OpenGLContext(mpWindow));

		mpContext->Init();

		glfwSetWindowUserPointer(mpWindow, &mData);
		SetVSync(true);

		//Set GLFW callback functions for events
		glfwSetWindowCloseCallback(mpWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.callback(e);
		});

		glfwSetWindowSizeCallback(mpWindow, [](GLFWwindow* window, int x, int y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = x;
			data.height = y;

			WindowResizeEvent e{ float(x), float(y) };
			
			data.callback(e);
		});

		glfwSetMouseButtonCallback(mpWindow, [](GLFWwindow* window, int button, int action, int mods)
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

		glfwSetKeyCallback(mpWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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

		glfwSetCharCallback(mpWindow, [](GLFWwindow* window, uint32_t key)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent e{ (int)key };
			data.callback(e);
		});

		glfwSetScrollCallback(mpWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e{ (float)xOffset, (float)yOffset };

			data.callback(e);
		});

		glfwSetCursorPosCallback(mpWindow, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e{ (float)x, (float)y };

			data.callback(e);
		});
	}

	uint32_t WindowsWindow::GetWidth() const
	{
		return mData.width;
	}

	uint32_t WindowsWindow::GetHeight() const
	{
		return mData.height;
	}

	void WindowsWindow::SetEventCallBack(const EventCallBack& callback)
	{
		mData.callback = callback;
	}

	bool WindowsWindow::IsVSync() const
	{
		return mData.vsync;
	}

	void WindowsWindow::SetVSync(bool vsync)
	{
		if (vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		mData.vsync = vsync;
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(mpWindow);
		glfwTerminate();
	}
}