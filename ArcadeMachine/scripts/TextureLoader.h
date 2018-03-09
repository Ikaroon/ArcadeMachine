#pragma once
#include "stdafx.h"
#include "TextureData.h"

class TextureLoader
{
public:
	static TextureData load(std::string path);
private:
	static GLuint loadBMP(std::string path);
};