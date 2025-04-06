#include "ImpPCH.h"
#include "Application.h"

#include <ranges>
#include "Log.h"
#include "Input.h"
#include "Imp/Imgui/ImguiLayer.h"
#include "Imp/Renderer/Renderer.h"
#include "Imp/Renderer/Renderer2D.h"
#include "Imp/Utils/PlatformUtils.h"


namespace Imp
{
	Ref<Application> Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification const& specification)
		: m_Specification(specification)
	{
		IMP_PROFILE_FUNCTION();

		IMP_CORE_ASSERT(!s_Instance, "Application already exists!");

		s_Instance.reset(this);

		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(specification.Name));
		m_Window->SetEventCallBack([this]<typename T0>(T0 && ph1) { return OnEvent(std::forward<T0>(ph1)); });
		m_Window->SetVSync(false);

		Renderer2D::Init();

		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Renderer2D::ShutDown();
	}

	void Application::PushLayer(const Ref<Layer>& layer)
	{
		m_LayerManager.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(const Ref<Layer>& overlay)
	{
		m_LayerManager.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(
			[this]<typename T0>(T0 && ph1) { return OnWindowClose(std::forward<T0>(ph1)); });

		for (auto const& layer : std::ranges::reverse_view(m_LayerManager))
		{

			layer->OnEvent(e);
			if (e.IsHandled())
			{
				break;
			}

		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		IMP_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::Run()
	{
		IMP_CORE_TRACE("Starting Application");
		while (m_Running)
		{

			float time = Time::GetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			RenderCommand::Clear();

			for (Ref<Layer> const& layer : m_LayerManager)
			{
				layer->Update(ts);
			}

			for (Ref<Layer> const& layer : m_LayerManager)
			{
				layer->Render();
			}

#ifdef IMP_DEBUG
			m_ImGuiLayer->Begin();
			for (Ref<Layer> const& layer : m_LayerManager)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
#endif
			m_Window->Update();
		}

		IMP_CORE_TRACE("Closing Application");
	}
}
