#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/WindowEvent.h"

namespace Imp
{
	class IMP_API Application
	{
	public:
		Application();

		virtual ~Application();

		virtual void OnEvent(Event& e);

		virtual bool OnWindowClose(WindowCloseEvent& e);

		virtual void Run();

		virtual void CleanUp();

	private:
		Window* m_pWindow;
		bool m_Running = true;

	};

	Application* CreateApplication();
}

