#pragma once
#include "stdafx.h"
#include "Mesh.h"

class MeshManager
{
public:
	virtual ~MeshManager()
	{
		clearLocal();
	};

	static MeshManager* instance()
	{
		static CGuard g;   // Dealocation
		if (!INSTANCE)
			INSTANCE = new MeshManager();
		return INSTANCE;
	}

	static void addMesh(std::string name, Mesh* mesh);
	void addMeshLocal(std::string name, Mesh* mesh);

	static Mesh* getMesh(std::string name);
	Mesh* getMeshLocal(std::string name);

	static void clear();
	void clearLocal();
private:
	MeshManager() {};
	MeshManager(const MeshManager&);
	static MeshManager* INSTANCE;

	std::map<std::string, Mesh*> m_Meshes;

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != MeshManager::INSTANCE)
			{
				delete MeshManager::INSTANCE;
				MeshManager::INSTANCE = NULL;
			}
		}
	};
};