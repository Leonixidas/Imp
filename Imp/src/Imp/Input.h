#pragma once
#include "Core.h"

namespace Imp
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return m_pInstance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return m_pInstance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return m_pInstance->GetMouseXImpl(); }
		inline static float GetMouseY() { return m_pInstance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePosition() { return m_pInstance->GetMousePositionImpl(); }

		inline static void ShutDown()
		{
			if (m_pInstance)  delete m_pInstance;
		}
	
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* m_pInstance;
	};
}