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
	explicit Camera(glm::vec3 const& pos, glm::vec3 const& rot)
		: m_Position(pos)
		, m_Rotation(rot)
		, m_View()
		, m_Proj()
	{
	}
	virtual ~Camera() = default;

	void Rotate(glm::vec3 const& rot);
	void Translate(glm::vec3 const& t);

	//getters
	glm::mat4 const& GetViewMatrix() { return m_View; }
	glm::mat4 const& GetProjectionMatrix() { return m_Proj; }
	glm::mat4 GetViewProjectionMatrix()	{return m_Proj * m_View;}

	glm::vec3 const& GetPosition() { return m_Position; }
	glm::vec3 const& GetRotationEuler() { return m_Rotation; }

	CameraType const& GetCameraType() { return m_Type; }

	//setters
	void SetPosition(glm::vec3 const& pos) { m_Position = pos; CalculateViewMatrix(); }
	void SetRotation(glm::vec3 const& rot) { m_Rotation = rot; CalculateViewMatrix(); }

	virtual void CalculateViewMatrix() = 0;
	virtual void CalculateProjectionMatrix() = 0;

protected:
	glm::vec3 m_Position, m_Rotation;
	glm::mat4 m_View, m_Proj;

	CameraType m_Type = CameraType::DEFAULT;
};

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(glm::vec3 const& pos, glm::vec3 const& rot, float nearPlane, float farPlane, float fov, float aspectRatio);
	~PerspectiveCamera() override = default;

	//getters
	float GetFOV() const { return m_FOVx; }
	float GetNear() const { return m_Near; }
	float GetFar() const { return m_Far; }
	float GetAspectRatio() const { return m_AspectRatio; }

	//setters
	void SetFOV(float const fov) { m_FOVx = fov; CalculateVerticalFOV(); }
	void SetNear(float const n) { m_Near = n;}
	void SetFar(float const f) { m_Far = f; }
	void SetAspectRatio(float const aspectRatio) {	m_AspectRatio = aspectRatio; CalculateVerticalFOV();	}

	//transforms
	void Translate(glm::vec3 const& t);
	void Rotate(glm::vec3 const& r);

	virtual void CalculateViewMatrix() override;
	virtual void CalculateProjectionMatrix() override;

private:
	void CalculateVerticalFOV();

	float m_FOVx, m_FOVy, m_Near, m_Far, m_AspectRatio;
};

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(glm::vec3 const& pos, glm::vec3 const& rot, float left, float right, float bottom, float top);
	virtual ~OrthographicCamera() override = default;

	virtual void CalculateProjectionMatrix() override;
	virtual void CalculateViewMatrix() override;

private:
	float m_Left, m_Right, m_Top, m_Bottom;
};
}


