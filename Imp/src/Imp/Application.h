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

		static Application& GetInstance() { return *m_pInstance; }

		Window& GetWindow() { return *m_pWindow; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		Window* m_pWindow;
		bool m_Running = true;
		LayerManager m_LayerManager;

		static Application* m_pInstance;
	};

	Application* CreateApplication();
}

