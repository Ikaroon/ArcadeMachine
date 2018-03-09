#include "TextureManager.h"

TextureManager* TextureManager::INSTANCE = NULL;

void TextureManager::addTexture(std::string name, Texture* texture)
{
	instance()->addTextureLocal(name, texture);
}

void TextureManager::addTextureLocal(std::string name, Texture* texture)
{
	if (m_Textures[name] != nullptr)
	{
		return;
	}

	Debug::log("Registered (Texture: " + name + ")");
	m_Textures[name] = texture;
}

Texture* TextureManager::getTexture(std::string name)
{
	return instance()->getTextureLocal(name);
}

Texture* TextureManager::getTextureLocal(std::string name)
{
	return m_Textures[name];
}

void TextureManager::clear()
{
	instance()->clearLocal();
}

void TextureManager::clearLocal()
{
	for (auto texture : m_Textures)
	{
		Debug::log("Deleted (Texture: " + texture.first + ")");
		delete texture.second;
	}
	m_Textures.clear();
}
