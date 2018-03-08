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
		return;
	}

	m_Materials.insert(std::pair<std::string, Material*>(name, material));
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
		delete material.second;
	}
	m_Materials.clear();
}
