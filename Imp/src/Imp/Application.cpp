#include "ImpPCH.h"
#include "Application.h"
#include "Log.h"
#include "glad/glad.h"


namespace Imp
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application()
		: m_LayerManager()
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

#ifdef IMP_DEBUG
		Log::Info(e.DebugInfo());
#endif

		for (auto iter = m_LayerManager.rBegin(); iter != m_LayerManager.rEnd();)
		{
			(*iter++)->OnEvent(e);
			if (e.IsHandeled())
				break;
		}

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
			for (auto iter = m_LayerManager.Begin(); iter != m_LayerManager.End();)
			{
				if((*iter)->GetEnabled())
					(*iter)->Update();

				++iter;
			}

			m_pWindow->Update();
		}
		Log::Info("Closing Application");
	}
	void Application::CleanUp()
	{
		delete m_pWindow;
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerManager.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerManager.PushOverlay(overlay);
	}
}