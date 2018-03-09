#pragma once
#include "stdafx.h"

typedef unsigned int uint;

class Texture
{
public:
	Texture(std::string name, std::string path);
	virtual ~Texture();

	GLuint get_ID();
private:
	GLuint m_TextureID;
	uint m_Width;
	uint m_Height;

};