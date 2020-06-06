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
		ImguiLayer* m_pImGuiLayer;
		bool m_Running = true;
		LayerManager m_LayerManager;

		static Application* m_pInstance;

		VertexArray* m_pVertexArray;
		VertexBuffer* m_pVertexBuffer;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
	};

	Application* CreateApplication();
}

