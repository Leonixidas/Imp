#include "ImpPCH.h"
#include "Imp/Renderer/OrthographicCameraController.h"

#include "Imp/Core/Input.h"

namespace Imp
{
	OrthographicCameraController::OrthographicCameraController(float const aspectRatio, bool const rotation)
		: m_AspectRatio(aspectRatio)
		, m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
		, m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep const ts)
	{
		IMP_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(Key::A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		IMP_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(IMP_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(IMP_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float const width, float const height)
	{
		m_AspectRatio = width / height;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		IMP_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetY() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		IMP_PROFILE_FUNCTION();

		OnResize(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
		return false;
	}
}
