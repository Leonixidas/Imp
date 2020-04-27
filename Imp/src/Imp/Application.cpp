#include "ImpPCH.h"
#include "Application.h"
#include "Log.h"


namespace Imp
{
	Application::Application()
	{
		m_pWindow = Window::Create();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		Log::Info("Entered Application: loop");
		while (m_Running)
		{
			m_pWindow->OnUpdate();
		}
	}
}