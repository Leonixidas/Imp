#include "ImpPCH.h"
#include "Imp/Core/Input.h"

#include "Imp/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Imp
{

	bool Input::IsKeyPressed(KeyCode const keycode)
	{
		auto const window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto const state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode const button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto const state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { static_cast<float>(xpos), static_cast<float>(ypos) };
	}
}