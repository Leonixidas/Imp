#pragma once
#include "Component.h"

namespace Imp
{
	class RenderComponent :	public Component
	{
	public:
		void SelectMesh(const std::string& name);
	};
}

