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

		static Application& GetInstance() { return *mpInstance; }

		void SetIsRunning(bool value) { mRunning = value; }

		Window& GetWindow() { return *mpWindow; }

		void PushLayer(const Ref<Layer>& layer);
		void PushOverlay(const Ref<Layer>& overlay);

		void SetLayerEnabled(const std::string& name, bool value);

	private:
		Ref<Window> mpWindow;
		Ref<ImguiLayer> mpImGuiLayer;
		bool mRunning = true;
		LayerManager mLayerManager;


		static Ref<Application> mpInstance;
	};

	Application* CreateApplication();
}

