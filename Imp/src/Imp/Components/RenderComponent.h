#pragma once
#include "Component.h"

namespace Imp
{
	class RenderComponent :	public Component
	{
	public:
		void SelectMesh(const uint8_t meshID);
		void SelectMaterial(const uint8_t matID);

	private:
		uint8_t m_MeshID, m_MaterialID;
	};
}

