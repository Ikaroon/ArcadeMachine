#include "TextureLoader.h"
#include "stdafx.h"
#include "stb_image.h"

TextureData TextureLoader::load(std::string path)
{
	GLuint textureID = NULL;
	int width;
	int height;
	int channels;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Debug::error("Failed to load texture: " + path);
	}
	stbi_image_free(data);

	Debug::log("Texture found: " + std::to_string(textureID) + " : " + std::to_string(width) + "x" + std::to_string(height));

	return TextureData{textureID, width, height};
}

GLuint TextureLoader::loadBMP(std::string path)
{
	return 0;
}