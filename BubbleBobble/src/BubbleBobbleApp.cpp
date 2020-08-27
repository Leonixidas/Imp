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
		IMP_INFO("CLIENT: ExampleLayer attached");

	}

	virtual void OnDetach() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("ExampleLayer");
		ImGui::Text("Hello It's a me!");
		ImGui::End(); 
	}

	virtual void Update() override
	{

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
	std::vector<float> m_VertexArray;
	Imp::Ref<Imp::VertexArray> m_VertexArray
};

class BubbleBobbleApp : public Imp::Application
{
public:
	BubbleBobbleApp()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~BubbleBobbleApp()
	{}
};

Imp::Application* Imp::CreateApplication()
{
	return new BubbleBobbleApp();
}