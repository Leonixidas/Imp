#include <Imp.h>
#pragma warning(push)
#pragma warning(disable:6011)
#include "Imgui/imgui.h"
#pragma warning(pop)

class ExampleLayer : public Imp::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer")
	{
		m_VertexArray = Imp::VertexArray::Create();
		Imp::RenderCommand::SetClearColor(glm::vec4(1, 1, 1, 1));
		Imp::RenderCommand::Clear();

		float vertices[3 * 7] =
		{
			100.f, 100.f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			400.f,  100.f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			250.f,  300.f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		Imp::Ref < Imp::VertexBuffer> vertexBuffer = Imp::VertexBuffer::Create(vertices, sizeof(vertices));
		Imp::BufferLayout layout =
		{
			{Imp::ShaderDataType::Float3, "a_Position"},
			{Imp::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		Imp::Ref<Imp::IndexBuffer> indexBuffer = Imp::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Imp::VertexArray::Create();

		float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Imp::Ref<Imp::VertexBuffer> squareVB = Imp::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Imp::ShaderDataType::Float3, "a_Position" },
			{ Imp::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Imp::Ref<Imp::IndexBuffer> squareIB = Imp::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

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

		m_Shader = Imp::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Imp::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		Imp::Window& window = Imp::Application::Get().GetWindow();
		m_WindowBounds = { window.GetWidth(), window.GetHeight() };
		m_Camera = Imp::OrthographicCamera(0.f, static_cast<float>(window.GetWidth()), 0.f, static_cast<float>(window.GetHeight()));
	}

	virtual void OnAttach() override
	{
		IMP_TRACE("ExampleLayer attached");
	}

	virtual void OnDetach() override
	{

	}

	virtual void Update(Imp::Timestep ts) override
	{
		Imp::RenderCommand::SetClearColor({ 0.f,0.f,0.f,1.f });
		Imp::RenderCommand::Clear();

		Imp::Renderer2D::BeginScene(m_Camera);
		Imp::Renderer2D::DrawQuad({ m_WindowBounds.x / 2,m_WindowBounds.y / 2 , -1 }, { 200.f,200.f }, { 1.f,0.f,1.f,1.f });
		Imp::Renderer2D::DrawQuad({ m_WindowBounds.x / 2,m_WindowBounds.y / 2 , 0 }, { 100.f,100.f }, { 1.f,1.f,1.f,1.f });
		Imp::Renderer2D::EndScene();

		Imp::Renderer::BeginScene(m_Camera);
		Imp::Renderer::Submit(m_Shader, m_VertexArray);
		Imp::Renderer::EndScene();
	}

	virtual void Render() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("ExampleLayer");
		ImVec2 size = ImGui::GetWindowSize();
		auto const id = Imp::Renderer::GetFrame();
		ImGui::GetWindowDrawList()->AddImage(id, ImVec2(0, 0), size);
		ImGui::End();
	}

	virtual void OnEvent(Imp::Event& e) override
	{
		Imp::EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<Imp::MouseMovedEvent>(IMP_BIND_EVENT_FN(OnMouseMovedEvent));
		dispatcher.Dispatch<Imp::WindowResizeEvent>(IMP_BIND_EVENT_FN(OnWindowResizeEvent));
	}

	bool OnMouseMovedEvent(Imp::MouseMovedEvent& e)
	{
		return false;
	}

	bool OnWindowResizeEvent(Imp::WindowResizeEvent& e)
	{
		m_Camera.SetProjection(0.f, static_cast<float>(e.GetWidth()), 0.f, static_cast<float>(e.GetHeight()));
		m_WindowBounds = { static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()) };
		return false;
	}

private:
	Imp::Ref<Imp::VertexArray> m_VertexArray;
	Imp::Ref<Imp::VertexArray> m_SquareVA;
	Imp::Ref<Imp::Shader> m_Shader;
	Imp::Ref<Imp::Shader> m_FlatColorShader;
	Imp::OrthographicCamera m_Camera;
	glm::vec2 m_WindowBounds;
};

class BubbleBobbleApp : public Imp::Application
{
public:
	explicit BubbleBobbleApp(const Imp::ApplicationSpecification& args)
		: Application(args)
	{
		PushLayer(Imp::CreateScope<ExampleLayer>(ExampleLayer()));
	}

	~BubbleBobbleApp() override = default;
};

Imp::Application* Imp::CreateApplication(ApplicationCommandLineArgs args)
{
	ApplicationSpecification props{};
	props.Name = "BubbleBobble";
	props.WorkingDirectory = "../BubbleBobble";
	props.CommandLineArgs = args;
	return new BubbleBobbleApp(props);
}