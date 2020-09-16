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
			if (name == "Mesh")
			{
				++Nr;
				Name = name + '_' + std::to_string(Nr);
			}
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

		void AddMesh(const Ref<Mesh>& mesh);
		//void DeleteMesh(uint32_t id);
		void DeleteMesh(const std::string& name);

		//Ref<VertexArray>& GetMesh(uint32_t id);
		Ref<Mesh>& GetMesh(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Mesh>> m_Meshes;
	};
}