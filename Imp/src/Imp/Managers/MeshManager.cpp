#include "ImpPCH.h"
#include "MeshManager.h"
#include "Imp/Log.h"

namespace Imp
{

	void MeshManager::AddMesh(const Ref<Mesh>& mesh)
	{
		if (mMeshes.find(mesh->Name) == mMeshes.end())
		{
			mMeshes[mesh->Name] = mesh;
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
		return mMeshes[name];
	}

}