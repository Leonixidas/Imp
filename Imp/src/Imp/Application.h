#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/WindowEvent.h"
#include "LayerManager.h"


namespace Imp
{
	class Application
	{
	public:
		Application();

		virtual ~Application();

		virtual void OnEvent(Event& e);

		virtual bool OnWindowClose(WindowCloseEvent& e);

		virtual void Run();

		virtual void CleanUp();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		Window* m_pWindow;
		bool m_Running = true;
		LayerManager m_LayerManager;
	};

	Application* CreateApplication();
}

