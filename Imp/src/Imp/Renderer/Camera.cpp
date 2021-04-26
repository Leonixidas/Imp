#include "ImpPCH.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/compatibility.hpp"
#include "glm/gtc/constants.hpp"


namespace Imp
{
	PerspectiveCamera::PerspectiveCamera(const glm::vec3& pos, const glm::vec3& rot, float nearPlane, float farPlane, float fov, float aspectratio)
		: Camera(pos, rot)
		, mNear(nearPlane)
		, mFar(farPlane)
		, mFOVx(fov)
		, mAspectRatio(aspectratio)
	{
		mType = CameraType::PERSPECTIVE;
		CalculateVerticalFOV();
		CalculateViewMatrix();
		CalculateProjectionMatrix();
	}

	void PerspectiveCamera::CalculateProjectionMatrix()
	{
		mProj = glm::perspectiveRH(mFOVy, mAspectRatio, mNear, mFar);
	}

	void PerspectiveCamera::CalculateVerticalFOV()
	{
		mFOVy = glm::atan(glm::tan(mFOVx / 2.f) * mAspectRatio) * 2;
	}

	void PerspectiveCamera::Translate(const glm::vec3& t)
	{
		mRotation += t;
		CalculateViewMatrix();
	}

	void PerspectiveCamera::Rotate(const glm::vec3& r)
	{
		mRotation += r;
		CalculateViewMatrix();
	}

	void PerspectiveCamera::CalculateViewMatrix()
	{
		glm::mat4 trans = glm::translate(glm::mat4(1), mPosition);
		glm::mat4 rot = glm::rotate(glm::mat4(1), mRotation.x, { 1,0,0 }) *
						glm::rotate(glm::mat4(1), mRotation.y, { 0,1,0 }) *
						glm::rotate(glm::mat4(1), mRotation.z, { 0,0,1 });

		mView = glm::inverse(trans * rot * glm::scale(glm::mat4(1), { 1.f,1.f,1.f }));
	}

	OrthographicCamera::OrthographicCamera(const glm::vec3& pos, const glm::vec3& rot, float left, float right, float bottom, float top)
		: Camera(pos, rot)
		, mLeft(left)
		, mRight(right)
		, mTop(top)
		, mBottom(bottom)
	{
		mType = CameraType::ORTHO;
		CalculateViewMatrix();
		CalculateProjectionMatrix();
	}

	void OrthographicCamera::CalculateProjectionMatrix()
	{
		mProj = glm::orthoRH(mLeft, mRight, mBottom, mTop, -1.f, 1.f);
	}

	void OrthographicCamera::CalculateViewMatrix()
	{
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), mPosition);
		glm::mat4 rot = glm::rotate(glm::mat4(1), mRotation.x, { 1,0,0 }) *
						glm::rotate(glm::mat4(1), mRotation.y, { 0,1,0 }) *
						glm::rotate(glm::mat4(1), mRotation.z, { 0,0,1 });

		mView = glm::inverse(trans * rot);
	}

	void Camera::Rotate(const glm::vec3& rot)
	{
		mRotation += rot;
	}

	void Camera::Translate(const glm::vec3& t)
	{
		mPosition += t;
	}

}