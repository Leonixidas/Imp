#pragma once
#include "Core.h"

namespace Imp
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return mpInstance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return mpInstance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return mpInstance->GetMouseXImpl(); }
		inline static float GetMouseY() { return mpInstance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePosition() { return mpInstance->GetMousePositionImpl(); }

		inline static void ShutDown()
		{
			if (mpInstance)  delete mpInstance;
		}
	
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* mpInstance;
	};
}