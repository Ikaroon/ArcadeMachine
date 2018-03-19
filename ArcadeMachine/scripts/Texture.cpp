#include "Texture.h"
#include "TextureManager.h"
#include "TextureLoader.h"

Texture::Texture(std::string name, std::string path, INTERPOLATION interpolation)
{
	TextureData data = TextureLoader::load(path, interpolation);
	m_TextureID = data.id;
	m_Width = data.width;
	m_Height = data.height;
	TextureManager::addTexture(name, this);
}

Texture::Texture(std::string name, std::string path) : Texture(name, path, INTERPOLATION::LINEAR) {}

Texture::Texture(std::string path) : Texture("unnamed", path) {}

Texture::~Texture()
{
}

GLuint Texture::get_ID()
{
	return m_TextureID;
}
