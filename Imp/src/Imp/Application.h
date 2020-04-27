#pragma once
#include "Core.h"
#include "Window.h"

namespace Imp
{
	class IMP_API Application
	{
	public:
		Application();

		virtual ~Application();

		virtual void Run();

	private:
		Window* m_pWindow;
		bool m_Running = true;

	};

	Application* CreateApplication();
}

