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
		addMeshLocal(name, 1, mesh);
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

void MeshManager::addMeshLocal(std::string name, int count, Mesh * mesh)
{
	std::string newName = name + "(" + std::to_string(count) + ")";
	if (m_Meshes[newName] != nullptr)
	{
		addMeshLocal(name, count + 1, mesh);
		return;
	}

	Debug::log("Registered (Mesh: " + newName + ")");
	m_Meshes[newName] = mesh;
}
