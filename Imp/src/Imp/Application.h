#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/WindowEvent.h"
#include "LayerManager.h"


namespace Imp
{
	class ImguiLayer;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class Camera;

	class Application
	{
	public:
		explicit Application(const WindowProps& props);

		virtual ~Application();

		virtual void OnEvent(Event& e);

		virtual bool OnWindowClose(WindowCloseEvent& e);

		virtual void Run();

		virtual void CleanUp();

		static Application& GetInstance() { return *m_pInstance; }

		void SetIsRunning(bool value) { m_Running = value; }

		Window& GetWindow() { return *m_pWindow; }

		void PushLayer(const Ref<Layer>& layer);
		void PushOverlay(const Ref<Layer>& overlay);

		void SetLayerEnabled(const std::string& name, bool value);

	private:
		Ref<Window> m_pWindow;
		Ref<ImguiLayer> m_pImGuiLayer;
		bool m_Running = true;
		LayerManager m_LayerManager;


		static Ref<Application> m_pInstance;
	};

	Application* CreateApplication();
}

