#pragma once

//I plan on continue using this engine for further development so I am using these macros for future purposes
#include "Log.h"

#ifdef IMP_WINDOWS

extern Imp::Application* Imp::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Imp::CreateApplication();
	app->Run();
	Imp::Log::Info("Apple");
	Imp::Log::CleanUp();
}
#endif