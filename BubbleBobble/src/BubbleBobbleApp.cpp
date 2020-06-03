#include <Imp.h>

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
};

class BubbleBobbleApp : public Imp::Application
{
public:
	BubbleBobbleApp()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Imp::ImguiLayer());
	}

	virtual ~BubbleBobbleApp()
	{}
};

Imp::Application* Imp::CreateApplication()
{
	return new BubbleBobbleApp();
}