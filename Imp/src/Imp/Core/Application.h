#pragma once
#include "Imp/Core/Base.h"
#include "Imp/Events/ApplicationEvent.h"
#include "Imp/Core/LayerManager.h"
#include "Imp/Core/Window.h"
#include "Imp/Imgui/ImguiLayer.h"

int main(int argc, char** argv);

namespace Imp
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			IMP_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Imp Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:
		explicit Application(ApplicationSpecification const& props);

		virtual ~Application();

		virtual void OnEvent(Event& e);

		void PushLayer(const Ref<Layer>& layer);
		void PushOverlay(const Ref<Layer>& overlay);

		Window& GetWindow() const { return *m_Window; }

		virtual void Close();

		Ref<ImGuiLayer> GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }

		ApplicationSpecification const& GetSpecification() const { return m_Specification; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationSpecification m_Specification;
		Ref<Window> m_Window;
		Ref<ImGuiLayer> m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerManager m_LayerManager;
		float m_LastFrameTime = 0.f;

		std::vector<std::function<void()>> m_MainThreadQueue;
		std::mutex m_MainThreadQueueMutex;

	private:
		static Ref<Application> s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication(ApplicationCommandLineArgs args);
}

