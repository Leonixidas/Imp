#include "ImpPCH.h"
#include "Application.h"
#include "Log.h"
#include "glad/glad.h"


namespace Imp
{
	Application* Application::m_pInstance = nullptr;

	Application::Application()
		: m_LayerManager()
	{
		if (m_pInstance != nullptr)
		{
			Log::Error("There already exists an application");
		}

		m_pInstance = this;
		m_pWindow = Window::Create();
		m_pWindow->SetEventCallBack(BIND_EVENT_FUNC(Application::OnEvent));
	}

	Application::~Application()
	{
		CleanUp();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));

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
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

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