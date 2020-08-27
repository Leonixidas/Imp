#pragma once
#include "Imp/Core.h"
#include "Imp/Renderer/VertexArray.h"
#include <unordered_map>
#include "Imp/Singleton.h"

namespace Imp
{
	class MeshManager : public Singleton<MeshManager>
	{
	public:
		MeshManager() {}
		~MeshManager() = default;

		void AddMesh(const Ref<VertexArray>& va, const std::string& name = "Mesh");
		void DeleteMesh(const std::string& name);

		Ref<VertexArray>& GetMesh();

	private:
		std::unordered_map<std::string, Ref<VertexArray>> m_Meshes;
	};
}