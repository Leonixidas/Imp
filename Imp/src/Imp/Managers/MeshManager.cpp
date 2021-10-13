#include "ImpPCH.h"
#include "MeshManager.h"
#include "Imp/Log.h"

namespace Imp
{

void MeshManager::AddMesh(Ref<Mesh> const& mesh)
{
	if (m_Meshes.find(mesh->m_Name) == m_Meshes.end())
	{
		m_Meshes[mesh->m_Name] = mesh;
	}
	else
	{
		Log::Error("Mesh with name '" + mesh->m_Name + "' already exists");
	}
}

void MeshManager::DeleteMesh(std::string const& name)
{

}

Ref<Mesh>& MeshManager::GetMesh(std::string const& name)
{
	return m_Meshes[name];
}

}