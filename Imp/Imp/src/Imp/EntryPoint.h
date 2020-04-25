#pragma once

#ifdef IMP_WINDOWS

extern Imp::Application* Imp::CreateApplication();

int main(int argc, char** argv)
{
	Imp::Log::GetInstance();
	Imp::Log::Info("ApplePie");
	Imp::Log::Destory();
	auto app = Imp::CreateApplication();
	app->Run();
	delete app;
}
#endif