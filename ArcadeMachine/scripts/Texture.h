#pragma once
#include "stdafx.h"

typedef unsigned int uint;

class Texture
{
public:
	enum class INTERPOLATION { LINEAR, BILINEAR };

	explicit Texture(std::string name, std::string path, INTERPOLATION interpolation);
	explicit Texture(std::string name, std::string path);
	Texture(std::string path);
	virtual ~Texture();

	GLuint get_ID();
private:
	GLuint m_TextureID;
	uint m_Width;
	uint m_Height;

};