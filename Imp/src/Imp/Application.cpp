#include "ImpPCH.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "Imgui/ImguiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"


namespace Imp
{
	Application* Application::m_pInstance = nullptr;

	

	Application::Application()
		: m_LayerManager()
	{
		if (m_pInstance != nullptr)
		{
			IMP_ERROR("There already exists an application");
		}

		m_pInstance = this;
		m_pWindow = Window::Create();
		m_pWindow->SetEventCallBack(BIND_EVENT_FUNC(Application::OnEvent));
	
		m_pImGuiLayer = new ImguiLayer();
		PushOverlay(m_pImGuiLayer);

		m_pVertexArray = VertexArray::Create();


		float vertices[3 * 7] =
		{
			-0.5f,-0.5f,0.0f, 0.8f,0.2f,0.5f,1.f,
			 0.5f,-0.5f,0.0f, 0.2f,0.5f,0.8f,1.f,
			 0.0f, 0.5f,0.0f, 0.5f,0.8f,0.2f,1.f,
		};

		m_pVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ShaderDataType::Float3, "vPosition"},
			{ShaderDataType::Float4, "vColor"}
		};

		m_pVertexBuffer->SetLayout(layout);
		
		m_pVertexArray->AddVertexBuffer(m_pVertexBuffer);
		

		uint32_t indices[3] = { 0,1,2 }; 
		m_pIndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_pVertexArray->SetIndexBuffer(m_pIndexBuffer);

		std::string vertexSrc = 
		R"(
			#version 430 core

			layout(location = 0) in vec3 vPosition;
			layout(location = 1) in vec4 vColor;

			out vec3 gPosition;
			out vec4 gColor;

			void main()
			{
				gColor = vColor;
				gPosition = vPosition * 0.5 + 0.5;
				gl_Position = vec4(vPosition, 1.0);
			}
		)";

		std::string pixelSrc =
		R"(
			#version 430 core
			
			layout(location = 0) out vec4 color;

			in vec3 gPosition;
			in vec4 gColor;

			void main()
			{
				color = vec4(gPosition,1.0);
				color = gColor;
			}
		)";

		m_pShader = Shader::Create(vertexSrc, pixelSrc);
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
			(*iter++)->OnEvent(e);
			if (e.IsHandeled())
				break;
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
			RenderCommand::SetClearColor({ 0.2f,0.2f,0.2f,1.f });
			RenderCommand::Clear();

			Renderer::BeginScene();
			m_pShader->Bind();
			Renderer::Submit(m_pVertexArray);
			Renderer::EndScene();

			for (Layer* layer : m_LayerManager)
			{
				if (layer->GetEnabled()) 
					layer->Update();
			}

			m_pImGuiLayer->Begin();
			for (Layer* layer : m_LayerManager)
			{
				if (layer->GetEnabled())
					layer->OnImGuiRender();
			}
			m_pImGuiLayer->End();

			auto [x, y] = Input::GetMousePosition();

			m_pWindow->Update();
		}
		RenderCommand::ShutDown();
		IMP_INFO("Closing Application");
	}
	void Application::CleanUp()
	{
		delete m_pWindow;
		delete m_pVertexArray;
		delete m_pVertexBuffer;
		delete m_pIndexBuffer;
		delete m_pShader;
		Input::ShutDown();
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerManager.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerManager.PushOverlay(overlay);
	}
}