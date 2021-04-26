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
			: mPosition(pos)
			, mRotation(rot)
			, mProj()
			, mView()
		{
		}
		virtual ~Camera() = default;
		
		void Rotate(const glm::vec3& rot);
		void Translate(const glm::vec3& t);

		//getters
		const glm::mat4& GetViewMatrix() { return mView; }
		const glm::mat4& GetProjectionMatrix() { return mProj; }
		glm::mat4 GetViewProjectionMatrix()	{return mProj * mView;}

		const glm::vec3& GetPosition() { return mPosition; }
		const glm::vec3& GetRotationEuler() { return mRotation; }

		const CameraType& GetCameraType() { return mType; }

		//setters
		void SetPosition(const glm::vec3& pos) { mPosition = pos; CalculateViewMatrix(); }
		void SetRotation(const glm::vec3& rot) { mRotation = rot; CalculateViewMatrix(); }

		virtual void CalculateViewMatrix() = 0;
		virtual void CalculateProjectionMatrix() = 0;

	protected:
		glm::mat4 mView, mProj;
		glm::vec3 mPosition, mRotation;

		CameraType mType = CameraType::DEFAULT;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(const glm::vec3& pos, const glm::vec3& rot, float nearPlane, float farPlane, float fov, float aspectratio);
		~PerspectiveCamera() = default;

		//getters
		float GetFOV() { return mFOVx; }
		float GetNear() { return mNear; }
		float GetFar() { return mFar; }
		float GetAspectRatio() { return mAspectRatio; }

		//setters
		void SetFOV(float fov) { mFOVx = fov; CalculateVerticalFOV(); }
		void SetNear(float n) { mNear = n;}
		void SetFar(float f) { mFar = f;}
		void SetAspectRatio(float ar) {	mAspectRatio = ar; CalculateVerticalFOV();	}

		//transforms
		void Translate(const glm::vec3& t);
		void Rotate(const glm::vec3& r);

		virtual void CalculateViewMatrix() override;
		virtual void CalculateProjectionMatrix() override;

	private:
		void CalculateVerticalFOV();

		float mFOVx, mFOVy, mNear, mFar, mAspectRatio;
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(const glm::vec3& pos, const glm::vec3& rot, float left, float right, float bottom, float top);
		virtual ~OrthographicCamera() = default;

		virtual void CalculateProjectionMatrix() override;
		virtual void CalculateViewMatrix() override;

	private:
		float mLeft, mRight, mTop, mBottom;
	};
}


