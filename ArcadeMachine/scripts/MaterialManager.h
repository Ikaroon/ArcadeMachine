#pragma once
#include "stdafx.h"
#include "Material.h"

class MaterialManager
{
public:
	virtual ~MaterialManager() {
		clearLocal();
	};

	static MaterialManager* instance()
	{
		static CGuard g;   // Dealocation
		if (!INSTANCE)
			INSTANCE = new MaterialManager();
		return INSTANCE;
	}

	static void addMaterial(std::string name, Material* material);
	void addMaterialLocal(std::string name, Material* material);

	static Material* getMaterial(std::string name);
	Material* getMaterialLocal(std::string name);

	static void clear();
	void clearLocal();

private:
	MaterialManager() {};
	MaterialManager(const MaterialManager&);
	static MaterialManager* INSTANCE;

	std::map<std::string, Material*> m_Materials;

	void addMaterialLocal(std::string name, int count, Material* material);

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != MaterialManager::INSTANCE)
			{
				delete MaterialManager::INSTANCE;
				MaterialManager::INSTANCE = NULL;
			}
		}
	};
};