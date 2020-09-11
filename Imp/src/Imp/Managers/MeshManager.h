#pragma once
#include "Imp/Core.h"
#include "Imp/Renderer/VertexArray.h"
#include <unordered_map>
#include "Imp/Singleton.h"

namespace Imp
{
	uint32_t Mesh::Nr = 0;
	struct Mesh
	{
		Mesh(const Ref<VertexArray>& va, const std::string& name = "Mesh")
			: VA(va)
		{
			
		}

		Ref<VertexArray> VA;
		std::string Name;

	private:
		static uint32_t Nr;
	};
	class MeshManager : public Singleton<MeshManager>
	{
	public:
		MeshManager() {}
		~MeshManager() = default;

		void AddMesh(const Ref<VertexArray>& va, const std::string& name = "Mesh");
		void DeleteMesh(uint32_t id);

		Ref<VertexArray>& GetMesh(uint32_t id);

	private:
		std::unordered_map<std::string, Ref<VertexArray>> m_Meshes;
	};
}