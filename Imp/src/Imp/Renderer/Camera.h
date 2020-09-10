#pragma once
#include "Imp/Core.h"
#include "glm/glm.hpp"

namespace Imp
{

	enum class CameraType : uint8_t
	{
		DEFAULT = 1 << 0,
		PERSPECTIVE = 1 << 1,
		ORTHO = 1 << 2
	};

	class Camera
	{
	public:
		explicit Camera(const glm::vec3& pos, const glm::vec3& rot)
			: m_Position(pos)
			, m_Rotation(rot)
			, m_Proj()
			, m_View()
		{
		}
		virtual ~Camera() = default;
		
		void Rotate(const glm::vec3& rot);
		void Translate(const glm::vec3& t);

		//getters
		const glm::mat4& GetViewMatrix() { return m_View; }
		const glm::mat4& GetProjectionMatrix() { return m_Proj; }
		glm::mat4 GetViewProjectionMatrix()	{return m_Proj * m_View;}

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetRotationEuler() { return m_Rotation; }

		const CameraType& GetCameraType() { return m_Type; }

		//setters
		void SetPosition(const glm::vec3& pos) { m_Position = pos; CalculateViewMatrix(); }
		void SetRotation(const glm::vec3& rot) { m_Rotation = rot; CalculateViewMatrix(); }

		virtual void CalculateViewMatrix() = 0;
		virtual void CalculateProjectionMatrix() = 0;

	protected:
		glm::mat4 m_View, m_Proj;
		glm::vec3 m_Position, m_Rotation;

		CameraType m_Type = CameraType::DEFAULT;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(const glm::vec3& pos, const glm::vec3& rot, float nearPlane, float farPlane, float fov, float aspectratio);
		~PerspectiveCamera() = default;

		//getters
		float GetFOV() { return m_FOVx; }
		float GetNear() { return m_Near; }
		float GetFar() { return m_Far; }
		float GetAspectRatio() { return m_AspectRatio; }

		//setters
		void SetFOV(float fov) { m_FOVx = fov; CalculateVerticalFOV(); }
		void SetNear(float n) { m_Near = n;}
		void SetFar(float f) { m_Far = f;}
		void SetAspectRatio(float ar) {	m_AspectRatio = ar; CalculateVerticalFOV();	}

		//transforms
		void Translate(const glm::vec3& t);
		void Rotate(const glm::vec3& r);

		virtual void CalculateViewMatrix() override;
		virtual void CalculateProjectionMatrix() override;

	private:
		void CalculateVerticalFOV();

		float m_FOVx, m_FOVy, m_Near, m_Far, m_AspectRatio;
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(const glm::vec3& pos, const glm::vec3& rot, float left, float right, float bottom, float top);
		virtual ~OrthographicCamera() = default;

		virtual void CalculateProjectionMatrix() override;
		virtual void CalculateViewMatrix() override;

	private:
		float m_Left, m_Right, m_Top, m_Bottom;
	};
}


