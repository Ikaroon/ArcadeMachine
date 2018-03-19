#pragma once
#include "stdafx.h"
#include "TextureData.h"
#include "Texture.h"

class TextureLoader
{
public:
	static TextureData load(std::string path, Texture::INTERPOLATION interpolation);
private:
	static GLuint loadBMP(std::string path);
};