#pragma once
#include "Imp/Core/Window.h"
#include "GLFW/glfw3.h"

namespace Imp
{
	class GraphicsContext;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;

		virtual void SetEventCallBack(const EventCallBack& callback) override;
		virtual bool IsVSync() const override;
		virtual void SetVSync(bool vsync) override;


		inline virtual void* GetNativeWindow() const override { return m_Window; }

	protected:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:
		GLFWwindow* m_Window;
		Ref<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title{};
			uint32_t Width{};
			uint32_t Height{};
			bool Vsync{};

			EventCallBack Callback{};
		};

		WindowData m_Data;

		bool m_Initialized = false;
	};
}

