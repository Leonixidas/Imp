#pragma once
#include "Imp/Core/Base.h"
#include "Imp/Core/Application.h"

#ifdef IMP_PLATFORM_WINDOWS

extern Imp::Application* Imp::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Imp::Log::Init();

	IMP_PROFILE_BEGIN_SESSION("Startup", "ImpProfile-Startup.json");
	auto app = Imp::CreateApplication({ .Count = argc, .Args = argv });
	IMP_PROFILE_END_SESSION();

	IMP_PROFILE_BEGIN_SESSION("Runtime", "ImpProfile-Runtime.json");
	app->Run();
	IMP_PROFILE_END_SESSION();

	IMP_PROFILE_BEGIN_SESSION("Shutdown", "ImpProfile-Shutdown.json");
	delete app;
	IMP_PROFILE_END_SESSION();
}
#endif