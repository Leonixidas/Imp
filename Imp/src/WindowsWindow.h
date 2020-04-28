#pragma once
#include "Imp/Window.h"
#include "GLFW/glfw3.h"

namespace Imp
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;

		virtual void SetEventCallBack(const EventCallBack& callback) override;
		virtual bool IsVSync() const override;
		virtual void SetVSync(bool vsync) override;

		virtual void OnUpdate() override;

	protected:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:
		GLFWwindow* m_pWindow;

		struct WindowData
		{
			std::string title{};
			unsigned int width{};
			unsigned int height{};
			bool vsync{};

			EventCallBack callback{};
		};

		WindowData m_Data;

		bool m_Initialized = false;
	};
}

