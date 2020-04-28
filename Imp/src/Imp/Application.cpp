#include "ImpPCH.h"
#include "Application.h"
#include "Log.h"


namespace Imp
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application::Application()
	{
		m_pWindow = Window::Create();
		m_pWindow->SetEventCallBack(BIND_EVENT_FUNC(OnEvent));
	}

	Application::~Application()
	{
		CleanUp();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		Log::Info("Starting Application");
		while (m_Running)
		{
			m_pWindow->OnUpdate();
		}
		Log::Info("Closing Application");
	}
	void Application::CleanUp()
	{
		delete m_pWindow;
	}
}