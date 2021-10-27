#pragma once
#include "Imp/Window.h"
#include "GLFW/glfw3.h"

namespace Imp
{
	class GraphicsContext;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;

		virtual void SetEventCallBack(const EventCallBack& callback) override;
		virtual bool IsVSync() const override;
		virtual void SetVSync(bool vsync) override;

		virtual void Update() override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }

	protected:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:
		GLFWwindow* m_Window;
		Ref<GraphicsContext> m_pContext;

		struct WindowData
		{
			std::string title{};
			uint32_t width{};
			uint32_t height{};
			bool vsync{};

			EventCallBack callback{};
		};

		WindowData m_Data;

		bool m_Initialized = false;
	};
}

