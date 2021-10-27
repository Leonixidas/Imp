#pragma once
#include "Core.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Imp
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode const keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

		inline static bool IsMouseButtonPressed(MouseCode const button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

		inline static void ShutDown()
		{
			if (s_Instance)  delete s_Instance;
		}

		virtual ~Input() = default;
	
	protected:
		virtual bool IsKeyPressedImpl(KeyCode const keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode const button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instance;
	};
}
