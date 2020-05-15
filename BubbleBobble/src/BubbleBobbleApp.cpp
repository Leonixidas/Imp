#include <Imp.h>

#define BIND_EVENT_FUNC(x) std::bind(&ExampleLayer::x,this,std::placeholders::_1)

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
		Imp::Log::Info("CLIENT: ExampleLayer attached");
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
		dispatcher.Dispatch<Imp::MouseMovedEvent>(BIND_EVENT_FUNC(OnMouseMovedEvent));
	}

	bool OnMouseMovedEvent(Imp::MouseMovedEvent& e)
	{
		Imp::Log::Info("CLIENT: " + e.DebugInfo());
		return true;
	}
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