#pragma once
#include "Camera.h"
#include "Imp/Core/Timestep.h"

namespace Imp
{
	class PerspectiveCamera: public Camera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep time);
	};
}
