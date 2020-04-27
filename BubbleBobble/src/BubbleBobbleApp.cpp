#include <Imp.h>

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