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
	}

	~ExampleLayer() = default;

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
		//ImVec2 size = ImGui::GetWindowSize();
		//void* id = Imp::Renderer::GetFrame();
		//ImGui::Image(ImTextureID(id), size);
		ImGui::End();
	}

	virtual void OnEvent(Imp::Event& e) override
	{
		Imp::EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<Imp::MouseMovedEvent>(BIND_EVENT_FUNC(ExampleLayer::OnMouseMovedEvent));
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
	BubbleBobbleApp(const Imp::WindowProps& props)
		: Application(props)
	{
		PushLayer(std::make_shared<ExampleLayer>(ExampleLayer()));
	}

	virtual ~BubbleBobbleApp()
	{}
};

Imp::Application* Imp::CreateApplication()
{
	WindowProps props{};
	props.m_Height = 720;
	props.m_Width = 1280;
	props.m_Title = "Example";
	return new BubbleBobbleApp(props);
}