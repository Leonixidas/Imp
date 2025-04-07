#pragma once
#include "Camera.h"
#include "Imp/Core/Timestep.h"
#include "Imp/Events/Event.h"
#include "Imp/Events/MouseEvent.h"

namespace Imp
{
	class PerspectiveCamera: public Camera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep time);
		void OnEvent(Event& e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float const distance) { m_Distance = distance; }

		inline void SetViewportSize(float const width, float const height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		glm::mat4 const& GetViewMatrix() const{ return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		glm::vec3 const& GetPosition() const { return m_Position; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }

	private:
		void UpdateProjection();
		void UpdateView();
		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(glm::vec2 const& delta);
		void MouseRotate(glm::vec2 const& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_Fov = 45.f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.f;

		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position = { 0.f, 0.f, 0.f };
		glm::vec3 m_FocalPoint = { 0.f, 0.f, 0.f };

		glm::vec2 m_InitialMousePosition = { 0.f, 0.f };

		float m_Distance = 10.f;
		float m_Pitch = 0.f, m_Yaw = 0.f;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};
}
