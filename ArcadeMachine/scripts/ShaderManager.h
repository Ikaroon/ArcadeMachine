#pragma once
#include "stdafx.h"
#include "Shader.h"

class ShaderManager
{
public:
	virtual ~ShaderManager()
	{
		clearLocal();
	};

	static ShaderManager* instance()
	{
		static CGuard g;   // Dealocation
		if (!INSTANCE)
			INSTANCE = new ShaderManager();
		return INSTANCE;
	}

	static void addShader(std::string name, Shader* shader);
	void addShaderLocal(std::string name, Shader* shader);

	static Shader* getShader(std::string name);
	Shader* getShaderLocal(std::string name);

	static void clear();
	void clearLocal();
private:
	ShaderManager() {};
	ShaderManager(const ShaderManager&);
	static ShaderManager* INSTANCE;

	std::map<std::string, Shader*> m_Shaders;

	void addShaderLocal(std::string name, int count, Shader* shader);

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != ShaderManager::INSTANCE)
			{
				delete ShaderManager::INSTANCE;
				ShaderManager::INSTANCE = NULL;
			}
		}
	};
};