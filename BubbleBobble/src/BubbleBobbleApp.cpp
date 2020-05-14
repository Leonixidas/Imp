#include <Imp.h>

//#define BIND_EVENT_FUNC(x) std::bind(&ExampleLayer::x,this,std::placeholders::_1)
//
//class ExampleLayer : public Imp::Layer
//{
//public:
//	ExampleLayer()
//		: Layer("Example Layer")
//	{}
//	
//	~ExampleLayer() = default;
//
//	virtual void OnAttach() override
//	{
//
//	}
//
//	virtual void OnDetach() override
//	{
//
//	}
//
//	virtual void Update() override
//	{
//
//	}
//
//	virtual void OnEvent(Imp::Event& e) override
//	{
//		Imp::EventDispatcher dispatcher{e};
//		dispatcher.Dispatch<Imp::KeyPressedEvent>(BIND_EVENT_FUNC(OnKeyEvent));
//	}
//
//	bool OnKeyEvent(Imp::KeyPressedEvent& e)
//	{
//		Imp::Log::Info(e.DebugInfo());
//		return true;
//	}
//};

class BubbleBobbleApp : public Imp::Application
{
public:
	BubbleBobbleApp()
	{}

	virtual ~BubbleBobbleApp()
	{}
};

Imp::Application* Imp::CreateApplication()
{
	return new BubbleBobbleApp();
}