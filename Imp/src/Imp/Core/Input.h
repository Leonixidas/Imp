#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"
#include "glm/glm.hpp"

namespace Imp
{
	class Input
	{
	public:

		static bool IsKeyPressed(KeyCode const keyCode);
		static bool IsMouseButtonPressed(MouseCode const button);

		static float GetMouseX();
		static float GetMouseY();
		static glm::vec2 GetMousePosition();
	};
}
