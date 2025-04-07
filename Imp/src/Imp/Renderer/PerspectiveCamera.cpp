#include <ImpPCH.h>
#include "PerspectiveCamera.h"

#include "Imp/Core/Input.h"
#include "Imp/Core/KeyCodes.h"
#include "Imp/Core/MouseCodes.h"

#include "GLFW/glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Imp
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
		, m_Fov(fov)
		, m_AspectRatio(aspectRatio)
		, m_NearClip(nearClip)
		, m_FarClip(farClip)
	{
		UpdateView();
	}

	void PerspectiveCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void PerspectiveCamera::UpdateView()
	{
		m_Position = CalculatePosition();
		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	std::pair<float, float> PerspectiveCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.f, 2.4f);
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f; //What are these numbers

		float y = std::min(m_ViewportHeight / 1000.f, 2.4f);
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float PerspectiveCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float PerspectiveCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.f);
		return speed;
	}

	void PerspectiveCamera::OnUpdate(Timestep time)
	{
		if (Input::IsKeyPressed(Key::LeftAlt))
		{
			glm::vec2 const& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
				MousePan(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
				MouseZoom(delta.y);
		}

		UpdateView();
	}

	void PerspectiveCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(IMP_BIND_EVENT_FN(PerspectiveCamera::OnMouseScroll));
	}

	bool PerspectiveCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetY() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}

	void PerspectiveCamera::MousePan(glm::vec2 const& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
	}

	void PerspectiveCamera::MouseRotate(glm::vec2 const& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.f : 1.f;
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();
	}

	void PerspectiveCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.f;
		}
	}

	glm::vec3 PerspectiveCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.f, 1.f, 0.f));
	}

	glm::vec3 PerspectiveCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.f, 0.f, 0.f));
	}

	glm::vec3 PerspectiveCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.f, 0.f, -1.f));
	}

	glm::vec3 PerspectiveCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	glm::quat PerspectiveCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
}
