#include "ImpPCH.h"
#include "MeshManager.h"
#include "Imp/Log.h"

namespace Imp
{

	void MeshManager::AddMesh(const Ref<Mesh>& mesh)
	{
		if (m_Meshes.find(mesh->Name) == m_Meshes.end())
		{
			m_Meshes[mesh->Name] = mesh;
		}
		else
		{
			Log::Error("Mesh with name '" + mesh->Name + "' already exists");
		}
	}

	void MeshManager::DeleteMesh(const std::string& name)
	{
		
	}

	Ref<Mesh>& MeshManager::GetMesh(const std::string& name)
	{
		return m_Meshes[name];
	}

}