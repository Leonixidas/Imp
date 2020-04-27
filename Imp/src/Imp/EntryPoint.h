#pragma once

//I plan on continue using this engine for further development so I am using these macros for future purposes

#ifdef IMP_WINDOWS

extern Imp::Application* Imp::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Imp::CreateApplication();
	app->Run();
	delete app;
}
#endif