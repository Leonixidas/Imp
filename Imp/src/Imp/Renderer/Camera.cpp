#include "ImpPCH.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/compatibility.hpp"
#include "glm/gtc/constants.hpp"


namespace Imp
{
	PerspectiveCamera::PerspectiveCamera(const glm::vec3& pos, const glm::vec3& rot, float nearPlane, float farPlane, float fov, float aspectratio)
		: Camera(pos, rot)
		, m_Near(nearPlane)
		, m_Far(farPlane)
		, m_FOVx(fov)
		, m_AspectRatio(aspectratio)
	{
		m_Type = CameraType::PERSPECTIVE;
		CalculateVerticalFOV();
		CalculateViewMatrix();
		CalculateProjectionMatrix();
	}

	void PerspectiveCamera::CalculateProjectionMatrix()
	{
		m_Proj = glm::perspectiveRH(m_FOVy, m_AspectRatio, m_Near, m_Far);
	}

	void PerspectiveCamera::CalculateVerticalFOV()
	{
		m_FOVy = glm::atan(glm::tan(m_FOVx / 2.f) * m_AspectRatio) * 2;
	}

	void PerspectiveCamera::Translate(const glm::vec3& t)
	{
		m_Rotation += t;
		CalculateViewMatrix();
	}

	void PerspectiveCamera::Rotate(const glm::vec3& r)
	{
		m_Rotation += r;
		CalculateViewMatrix();
	}

	void PerspectiveCamera::CalculateViewMatrix()
	{
		glm::mat4 trans = glm::translate(glm::mat4(1), m_Position);
		glm::mat4 rot = glm::rotate(glm::mat4(1), m_Rotation.x, { 1,0,0 }) *
						glm::rotate(glm::mat4(1), m_Rotation.y, { 0,1,0 }) *
						glm::rotate(glm::mat4(1), m_Rotation.z, { 0,0,1 });

		m_View = glm::inverse(trans * rot * glm::scale(glm::mat4(1), { 1.f,1.f,1.f }));
	}

	OrthographicCamera::OrthographicCamera(const glm::vec3& pos, const glm::vec3& rot, float left, float right, float bottom, float top)
		: Camera(pos, rot)
		, m_Left(left)
		, m_Right(right)
		, m_Top(top)
		, m_Bottom(bottom)
	{
		m_Type = CameraType::ORTHO;
		CalculateViewMatrix();
		CalculateProjectionMatrix();
	}

	void OrthographicCamera::CalculateProjectionMatrix()
	{
		m_Proj = glm::orthoRH(m_Left, m_Right, m_Bottom, m_Top, -1.f, 1.f);
	}

	void OrthographicCamera::CalculateViewMatrix()
	{
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 rot = glm::rotate(glm::mat4(1), m_Rotation.x, { 1,0,0 }) *
						glm::rotate(glm::mat4(1), m_Rotation.y, { 0,1,0 }) *
						glm::rotate(glm::mat4(1), m_Rotation.z, { 0,0,1 });

		m_View = glm::inverse(trans * rot);
	}

	void Camera::Rotate(const glm::vec3& rot)
	{
		m_Rotation += rot;
	}

	void Camera::Translate(const glm::vec3& t)
	{
		m_Position += t;
	}

}