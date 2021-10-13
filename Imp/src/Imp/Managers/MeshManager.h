#pragma once
#include "Imp/Core.h"
#include "Imp/Renderer/VertexArray.h"
#include <unordered_map>
#include "Imp/Singleton.h"


namespace Imp
{
class Mesh
{
public:
	Mesh(Ref<VertexArray> const& va, std::string const& name = "Mesh")
		: m_VA(va)
	{
		if (name == "Mesh")
		{
			++m_Nr;
			m_Name = name + '_' + std::to_string(m_Nr);
		}
	}

	Ref<VertexArray> m_VA;
	std::string m_Name;

private:
	static uint32_t m_Nr;
};

class MeshManager : public Singleton<MeshManager>
{
public:
	MeshManager() {}
	~MeshManager() = default;

	void AddMesh(Ref<Mesh> const& mesh);
	void DeleteMesh(std::string const& name);

	Ref<Mesh>& GetMesh(std::string const& name);

private:
	std::unordered_map<std::string, Ref<Mesh>> m_Meshes;
};
}