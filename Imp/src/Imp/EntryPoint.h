#pragma once

#ifdef IMP_WINDOWS

extern Imp::Application* Imp::CreateApplication();

int main(int argc, char** argv)
{
	Imp::Log::Init();
	auto app = Imp::CreateApplication();
	app->Run();

}
#endif