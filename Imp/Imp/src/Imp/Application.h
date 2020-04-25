#pragma once
#include "Core.h"

namespace Imp
{
	class IMP_API Application
	{
	public:
		Application();

		virtual ~Application();

		virtual void Run();
	};

	Application* CreateApplication();
}

