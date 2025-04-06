#pragma once
#include "glm/glm.hpp"

namespace Imp
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		glm::vec3 const& GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3 const& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float const rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		glm::mat4 const& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 const& GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 const& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		virtual ~OrthographicCamera() = default;

		virtual void CalculateProjectionMatrix();
		virtual void CalculateViewMatrix();
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.f,0.f,0.f };
		float m_Rotation = 0.f;
	};
}
