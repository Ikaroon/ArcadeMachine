#include "MeshManager.h"

MeshManager* MeshManager::INSTANCE = NULL;

void MeshManager::addMesh(std::string name, Mesh * mesh)
{
	instance()->addMeshLocal(name, mesh);
}

void MeshManager::addMeshLocal(std::string name, Mesh * mesh)
{
	if (m_Meshes[name] != nullptr)
	{
		return;
	}

	Debug::log("Registered (Mesh: " + name + ")");
	m_Meshes[name] = mesh;
}

Mesh * MeshManager::getMesh(std::string name)
{
	return instance()->getMeshLocal(name);
}

Mesh * MeshManager::getMeshLocal(std::string name)
{
	return m_Meshes[name];
}

void MeshManager::clear()
{
	instance()->clearLocal();
}

void MeshManager::clearLocal()
{
	for (auto mesh : m_Meshes)
	{
		Debug::log("Deleted (Mesh: " + mesh.first + ")");
		delete mesh.second;
	}
	m_Meshes.clear();
}
