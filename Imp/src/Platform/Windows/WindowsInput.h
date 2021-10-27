#pragma once
#include "Imp/Input.h"

namespace Imp
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode const keycode) override;

		virtual bool IsMouseButtonPressedImpl(MouseCode const button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}

