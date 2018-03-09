#include "ShaderManager.h"

ShaderManager* ShaderManager::INSTANCE = NULL;

void ShaderManager::addShader(std::string name, Shader * material)
{
	instance()->addShaderLocal(name, material);
}

void ShaderManager::addShaderLocal(std::string name, Shader * material)
{
	if (m_Shaders[name] != nullptr)
	{
		return;
	}

	Debug::log("Registered (Shader: " + name + ")");
	m_Shaders[name] = material;
}

Shader * ShaderManager::getShader(std::string name)
{
	return instance()->getShaderLocal(name);
}

Shader * ShaderManager::getShaderLocal(std::string name)
{
	return m_Shaders[name];
}

void ShaderManager::clear()
{
	instance()->clearLocal();
}

void ShaderManager::clearLocal()
{
	for (auto shader : m_Shaders)
	{
		Debug::log("Deleted (Shader: " + shader.first + ")");
		delete shader.second;
	}
	m_Shaders.clear();
}
