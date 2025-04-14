#pragma once
#include "Imp/Renderer/OrthographicCamera.h"
#include "Imp/Core/Timestep.h"
#include "Imp/Events/ApplicationEvent.h"
#include "Imp/Events/Event.h"
#include "Imp/Events/MouseEvent.h"

namespace Imp
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		OrthographicCamera const& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float const level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.f,0.f,0.f };
		float m_CameraRotation = 0.f;
		float m_CameraTranslationSpeed = 5.f, m_CameraRotationSpeed = 180.f;
	};
}
