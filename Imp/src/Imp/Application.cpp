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
	Ref<Application> Application::mpInstance = nullptr;

	Application::Application(const WindowProps& props)
		: mLayerManager()
	{
		if (mpInstance != nullptr)
		{
			IMP_ERROR("There already exists an application");
		}

		mpInstance.reset(this);
		mpWindow = Window::Create(props);
		mpWindow->SetEventCallBack(BIND_EVENT_FUNC(Application::OnEvent));
		mpWindow->SetVSync(false);

		Renderer2D::Init();
		Time::GetInstance()->Initialize();
	
		mpImGuiLayer = std::make_shared<ImguiLayer>();
		PushOverlay(mpImGuiLayer);

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

		for (auto iter = mLayerManager.rbegin(); iter != mLayerManager.rend();)
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
		mRunning = false;
		return true;
	}

	void Application::Run()
	{
		IMP_INFO("Starting Application");
		while (mRunning)
		{
			Imp::RenderCommand::SetClearColor({ 1.0f,0.f,1.f,1.f });
			Imp::RenderCommand::Clear();

			Time::GetInstance()->Update();

			for (Ref<Layer> layer : mLayerManager)
			{
				if (layer->GetEnabled()) 
					layer->Update();
			}

			for (Ref<Layer> layer : mLayerManager)
			{
				if (layer->GetEnabled())
					layer->Render();
			}

			//PhysicsManager::Render();
#ifdef IMP_DEBUG
			mpImGuiLayer->Begin();
			for (Ref<Layer> layer : mLayerManager)
			{
				if (layer->GetEnabled())
					layer->OnImGuiRender();
			}
			mpImGuiLayer->End();
#endif
			mpWindow->Update();
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
		mLayerManager.PushLayer(layer);
	}
	void Application::PushOverlay(const Ref<Layer>& overlay)
	{
		mLayerManager.PushOverlay(overlay);
	}

	void Application::SetLayerEnabled(const std::string& name, bool value)
	{
		for (Ref<Layer> layer : mLayerManager)
		{
			if (layer->GetName() == name)
				layer->SetEnabled(value);
		}
	}
}