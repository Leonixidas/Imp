#include "ImpPCH.h"
#include "Application.h"
#include "Time.h"
#include "Log.h"
#include "Input.h"
#include "Imgui/ImguiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"


namespace Imp
{
	Ref<Application> Application::m_pInstance = nullptr;

	Application::Application(const WindowProps& props)
		: m_LayerManager()
	{
		if (m_pInstance != nullptr)
		{
			IMP_ERROR("There already exists an application");
		}

		m_pInstance.reset(this);
		m_pWindow = Window::Create(props);
		m_pWindow->SetEventCallBack(BIND_EVENT_FUNC(Application::OnEvent));
		m_pWindow->SetVSync(false);

		Renderer2D::Init();
		Time::GetInstance()->Initialize();
	
		m_pImGuiLayer = std::make_shared<ImguiLayer>();
		PushOverlay(m_pImGuiLayer);

		//Imp::Renderer2D::LoadFont("Assets/Fonts/GameFont.fnt");
		//Imp::Renderer2D::LoadFont("Assets/Fonts/Arial.fnt");

	}

	Application::~Application()
	{
		CleanUp();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));

		for (auto iter = m_LayerManager.rbegin(); iter != m_LayerManager.rend();)
		{
			if ((*iter)->GetEnabled())
			{
				(*iter++)->OnEvent(e);
				if (e.IsHandeled())
					break;
			}
			else ++iter;
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		IMP_INFO("Starting Application");
		while (m_Running)
		{
			Imp::RenderCommand::SetClearColor({ 1.0f,0.f,1.f,1.f });
			Imp::RenderCommand::Clear();

			Time::GetInstance()->Update();

			for (Ref<Layer> layer : m_LayerManager)
			{
				if (layer->GetEnabled()) 
					layer->Update();
			}

			for (Ref<Layer> layer : m_LayerManager)
			{
				if (layer->GetEnabled())
					layer->Render();
			}

			//PhysicsManager::Render();
#ifdef IMP_DEBUG
			m_pImGuiLayer->Begin();
			for (Ref<Layer> layer : m_LayerManager)
			{
				if (layer->GetEnabled())
					layer->OnImGuiRender();
			}
			m_pImGuiLayer->End();
#endif
			m_pWindow->Update();
		}

		IMP_INFO("Closing Application");
	}
	void Application::CleanUp()
	{
		Input::ShutDown();
		Renderer2D::ShutDown();
		Time::Destory();
	}
	void Application::PushLayer(const Ref<Layer>& layer)
	{
		m_LayerManager.PushLayer(layer);
	}
	void Application::PushOverlay(const Ref<Layer>& overlay)
	{
		m_LayerManager.PushOverlay(overlay);
	}

	void Application::SetLayerEnabled(const std::string& name, bool value)
	{
		for (Ref<Layer> layer : m_LayerManager)
		{
			if (layer->GetName() == name)
				layer->SetEnabled(value);
		}
	}
}