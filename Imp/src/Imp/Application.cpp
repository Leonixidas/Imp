#include "ImpPCH.h"
#include "Application.h"
#include "Log.h"
#include "glad/glad.h"
#include "Input.h"
#include "Imgui/ImguiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"


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


		float vertices[3 * 3] =
		{
			-0.5f,-0.5f,0.0f,
			 0.5f,-0.5f,0.0f,
			 0.0f, 0.5f,0.0f
		};

		m_pVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0,1,2 };
		m_pIndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		std::string vertexSrc = 
		R"(
			#version 430 core

			layout(location = 0) in vec3 vPosition;

			out vec3 gPosition;

			void main()
			{
				gPosition = vPosition * 0.5 + 0.5;
				gl_Position = vec4(vPosition, 1.0);
			}
		)";

		std::string pixelSrc =
		R"(
			#version 430 core
			
			layout(location = 0) out vec4 color;

			in vec3 gPosition;

			void main()
			{
				color = vec4(gPosition,1.0);
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
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_pShader->Bind();
			m_pVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_pIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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