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
	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification const& specification)
		: m_Specification(specification)
	{
		IMP_PROFILE_FUNCTION();

		IMP_CORE_ASSERT(!s_Instance, "Application already exists!");

		s_Instance = this;

		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(specification.Name));
		m_Window->SetEventCallBack(IMP_BIND_EVENT_FN(Application::OnEvent));

		Renderer2D::Init();

		m_ImGuiLayer = CreateRef<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Renderer::ShutDown();
	}

	void Application::PushLayer(const Ref<Layer>& layer)
	{
		IMP_PROFILE_FUNCTION();
		m_LayerManager.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(const Ref<Layer>& overlay)
	{
		IMP_PROFILE_FUNCTION();
		m_LayerManager.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(IMP_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(IMP_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto const& layer : std::ranges::reverse_view(m_LayerManager))
		{
			if (e.IsHandled())
				break;

			layer->OnEvent(e);
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
			IMP_PROFILE_SCOPE("RunLoop");

			float time = Time::GetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Ref<Layer> const& layer : m_LayerManager)
				{
					layer->Update(ts);
				}

				for (Ref<Layer> const& layer : m_LayerManager)
				{
					layer->Render();
				}

				m_ImGuiLayer->Begin();
				for (Ref<Layer> const& layer : m_LayerManager)
				{
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}

		IMP_CORE_TRACE("Closing Application");
	}
}
