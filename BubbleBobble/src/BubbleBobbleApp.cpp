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
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
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
			#version 330 core
			
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
			#version 330 core
			
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
			#version 330 core
			
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
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Imp::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	}

	~ExampleLayer() override = default;

	virtual void OnAttach() override
	{
		IMP_TRACE("ExampleLayer attached");
	}

	virtual void OnDetach() override
	{

	}

	virtual void Update( Imp::Timestep ts) override
	{

	}

	virtual void Render() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("ExampleLayer");
		ImGui::Text("Hello It's a me!");
		ImVec2 size = ImGui::GetWindowSize();
		auto const id = Imp::Renderer::GetFrame();
		ImGui::GetWindowDrawList()->AddImage(id, ImVec2(0, 0), size);
		ImGui::End();
	}

	virtual void OnEvent(Imp::Event& e) override
	{
		Imp::EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<Imp::MouseMovedEvent>([this]<typename T0>(T0 && ph1)
		{
			return OnMouseMovedEvent(std::forward<T0>(ph1));
		});
	}

	bool OnMouseMovedEvent(Imp::MouseMovedEvent& e)
	{
		return true;
	}

private:
	Imp::Ref<Imp::VertexArray> m_VertexArray;
	Imp::Ref<Imp::VertexArray> m_SquareVA;
	Imp::Ref<Imp::Shader> m_Shader;
	Imp::Ref<Imp::Shader> m_FlatColorShader;
};

class BubbleBobbleApp : public Imp::Application
{
public:
	explicit BubbleBobbleApp(const Imp::ApplicationSpecification& args)
		: Application(args)
	{
		PushLayer(std::make_shared<ExampleLayer>(ExampleLayer()));
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