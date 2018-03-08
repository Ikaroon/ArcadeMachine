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

	m_Meshes.insert(std::pair<std::string, Mesh*>(name, mesh));
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
	for (auto material : m_Meshes)
	{
		delete material.second;
	}
	m_Meshes.clear();
}
