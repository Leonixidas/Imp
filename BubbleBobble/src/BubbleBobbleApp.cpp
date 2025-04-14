#include <Imp.h>
#pragma warning(push)
#pragma warning(disable:6011)
#include "Imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "Imp/Renderer/FrameBuffer.h"
#include "Imp/Renderer/OrthographicCameraController.h"
#pragma warning(pop)

namespace Imp
{
	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			: Layer("Example Layer")
			, m_CameraController(1280.f/720.f)
		{

		}

		virtual void OnAttach() override
		{
			IMP_TRACE("ExampleLayer attached");

			Window& window = Application::Get().GetWindow();
			m_WindowBounds = { window.GetWidth(), window.GetHeight() };

			FrameBufferSpecification spec;
			spec.Attachment = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::Depth };
			spec.Width = 1280;
			spec.Height = 720;
			m_FrameBuffer = FrameBuffer::Create(spec);

			m_VertexArray = VertexArray::Create();
			RenderCommand::SetClearColor(glm::vec4(1, 1, 1, 1));
			RenderCommand::Clear();

			Vertex vertices[3]
			{
				{.pos= {m_WindowBounds.x / 3.f, m_WindowBounds.y / 3.f, 0.0f}, .color= {0.8f, 0.2f, 0.8f, 1.0f}},
				{.pos = {m_WindowBounds.x - m_WindowBounds.x / 3.f,  m_WindowBounds.y / 3.f, 0.0f}, .color = {0.2f, 0.3f, 0.8f, 1.0f}},
				{.pos = {m_WindowBounds.x * 0.5f,  m_WindowBounds.y - m_WindowBounds.y / 3.f, 0.0f}, .color = {0.8f, 0.8f, 0.2f, 1.0f}}
			};

			Ref < VertexBuffer> const vertexBuffer = VertexBuffer::Create(reinterpret_cast<float*>(&vertices[0]), sizeof(vertices));
			BufferLayout const layout =
			{
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color" }
			};

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0,1,2 };
			Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
			m_VertexArray->SetIndexBuffer(indexBuffer);

			std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

			std::string fragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

			m_Shader = Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
		}

		virtual void OnDetach() override
		{

		}

		virtual void OnUpdate(Timestep const ts) override
		{
			IMP_PROFILE_FUNCTION();

			if (FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
				m_ViewportSize.x > 0.f && m_ViewportSize.y > 0.f && 
				(spec.Width != static_cast<uint32_t>(m_ViewportSize.x) || spec.Height != static_cast<uint32_t>(m_ViewportSize.y)))
			{
				m_FrameBuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
				m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			}

			Renderer2D::ResetStats();
			m_FrameBuffer->Bind();
			RenderCommand::SetClearColor({ 0.f,0.f,0.f,1.f });
			RenderCommand::Clear();

			m_FrameBuffer->ClearAttachment(1, -1);

			m_CameraController.OnUpdate(ts);

			OnOverlayRender();

			m_FrameBuffer->UnBind();
		}

		void OnOverlayRender()
		{
			Renderer2D::BeginScene(m_CameraController.GetCamera());
			Renderer2D::DrawQuad({ m_WindowBounds.x / 2,m_WindowBounds.y / 2 , -1 }, { 200.f,200.f }, { 1.f,0.f,1.f,1.f });
			Renderer2D::DrawQuad({ m_WindowBounds.x / 2,m_WindowBounds.y / 2 , 0 }, { 100.f,100.f }, { 1.f,1.f,1.f,1.f });
			Renderer2D::EndScene();

			Renderer::BeginScene(m_CameraController.GetCamera());
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::EndScene();
		}

		virtual void Render() override
		{
		}

		virtual void OnImGuiRender() override
		{
			auto dockSpaceId = ImGui::DockSpaceOverViewport();
			auto nodeId = ImGui::DockBuilderAddNode();

			if (ExampleOpen)
			{
				ImGui::Begin("Viewport", &ExampleOpen);

				auto size = ImGui::GetContentRegionAvail();
				m_ViewportSize = { size.x, size.y };

				auto const id = Renderer::GetFrame();

				ImGui::Image(id, size, { 0.f, 1.f }, { 1.f,0.f });
				ImGui::End();
			}
		}

		virtual void OnEvent(Event& e) override
		{
			EventDispatcher dispatcher{ e };
			dispatcher.Dispatch<MouseMovedEvent>(IMP_BIND_EVENT_FN(OnMouseMovedEvent));
			dispatcher.Dispatch<WindowResizeEvent>(IMP_BIND_EVENT_FN(OnWindowResizeEvent));
		}

		bool OnMouseMovedEvent(MouseMovedEvent& e)
		{
			return false;
		}

		bool OnWindowResizeEvent(WindowResizeEvent& e)
		{
			m_WindowBounds = { static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()) };
			return false;
		}

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
		Ref<FrameBuffer> m_FrameBuffer;
		OrthographicCameraController m_CameraController;
		glm::vec2 m_WindowBounds;
		glm::vec2 m_ViewportSize;

		bool ExampleOpen = true;
	};

	class BubbleBobbleApp : public Application
	{
	public:
		explicit BubbleBobbleApp(const ApplicationSpecification& args)
			: Application(args)
		{
			PushLayer(CreateScope<ExampleLayer>(ExampleLayer()));
		}

		~BubbleBobbleApp() override = default;
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification props{};
		props.Name = "BubbleBobble";
		props.WorkingDirectory = "../BubbleBobble";
		props.CommandLineArgs = args;
		return new BubbleBobbleApp(props);
	}
}
