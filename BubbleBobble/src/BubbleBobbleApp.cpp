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
		Imp::RenderCommand::SetClearColor(glm::vec4(1, 1, 1, 1));
		Imp::RenderCommand::Clear();
	}

	~ExampleLayer() override = default;

	virtual void OnAttach() override
	{
		IMP_TRACE("ExampleLayer attached");
	}

	virtual void OnDetach() override
	{

	}

	virtual void Update() override
	{

	}

	virtual void Render() override
	{
		
	}

	virtual void OnEnabled() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("ExampleLayer");
		ImGui::Text("Hello It's a me!");
		ImVec2 size = ImGui::GetWindowSize();
		auto const id = Imp::Renderer::GetFrame();
		ImGui::GetWindowDrawList()->AddImage(id, ImVec2(0,0), size);
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
};

class BubbleBobbleApp : public Imp::Application
{
public:
	explicit BubbleBobbleApp(const Imp::WindowProps& props)
		: Application(props)
	{
		PushLayer(std::make_shared<ExampleLayer>(ExampleLayer()));
	}

	~BubbleBobbleApp() override = default;
};

Imp::Application* Imp::CreateApplication()
{
	WindowProps props{};
	props.m_Height = 720;
	props.m_Width = 1280;
	props.m_Title = "Example";
	return new BubbleBobbleApp(props);
}