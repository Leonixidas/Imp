#pragma once
#include "Imp/Core.h"

namespace Imp
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}