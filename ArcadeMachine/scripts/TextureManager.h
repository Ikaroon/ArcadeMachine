#pragma once
#include "stdafx.h"
#include "Texture.h"

class TextureManager
{
public:
	virtual ~TextureManager()
	{
		clearLocal();
	};

	static TextureManager* instance()
	{
		static CGuard g;   // Dealocation
		if (!INSTANCE)
			INSTANCE = new TextureManager();
		return INSTANCE;
	}

	static void addTexture(std::string name, Texture* texture);
	void addTextureLocal(std::string name, Texture* texture);

	static Texture* getTexture(std::string name);
	Texture* getTextureLocal(std::string name);

	static void clear();
	void clearLocal();
private:
	TextureManager() {};
	TextureManager(const TextureManager&);
	static TextureManager* INSTANCE;

	std::map<std::string, Texture*> m_Textures;

	void addTextureLocal(std::string name, int count, Texture* texture);

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != TextureManager::INSTANCE)
			{
				delete TextureManager::INSTANCE;
				TextureManager::INSTANCE = NULL;
			}
		}
	};
};