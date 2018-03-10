#include "MaterialManager.h"

MaterialManager* MaterialManager::INSTANCE = NULL;

void MaterialManager::addMaterial(std::string name, Material * material)
{
	instance()->addMaterialLocal(name, material);
}

void MaterialManager::addMaterialLocal(std::string name, Material * material)
{
	if (m_Materials[name] != nullptr)
	{
		addMaterialLocal(name, 1, material);
		return;
	}

	Debug::log("Registered (Material: " + name + ")");
	m_Materials[name] = material;
}

Material * MaterialManager::getMaterial(std::string name)
{
	return instance()->getMaterialLocal(name);
}

Material * MaterialManager::getMaterialLocal(std::string name)
{
	return m_Materials[name];
}

void MaterialManager::clear()
{
	instance()->clearLocal();
}

void MaterialManager::clearLocal()
{
	for (auto material : m_Materials)
	{
		Debug::log("Deleted (Material: " + material.first + ")");
		delete material.second;
	}
	m_Materials.clear();
}

void MaterialManager::addMaterialLocal(std::string name, int count, Material * material)
{
	std::string newName = name + "(" + std::to_string(count) + ")";
	if (m_Materials[newName] != nullptr)
	{
		addMaterialLocal(name, count + 1, material);
		return;
	}

	Debug::log("Registered (Material: " + newName + ")");
	m_Materials[newName] = material;
}
