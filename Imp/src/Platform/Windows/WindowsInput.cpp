#include "ImpPCH.h"
#include "WindowsInput.h"

#include "Imp/Application.h"
#include <GLFW/glfw3.h>

Imp::Input* Imp::Input::mpInstance = new WindowsInput();

bool Imp::WindowsInput::IsKeyPressedImpl(int keycode)
{
	auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
	auto state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Imp::WindowsInput::IsMouseButtonPressedImpl(int button)
{
	auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

float Imp::WindowsInput::GetMouseXImpl()
{
	auto [x, y] = GetMousePositionImpl();
	return x;
}

float Imp::WindowsInput::GetMouseYImpl()
{
	auto [x, y] = GetMousePositionImpl();
	return y;
}

std::pair<float, float> Imp::WindowsInput::GetMousePositionImpl()
{
	auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return { (float)xpos, (float)ypos };
}
