#pragma once
#include "stdafx.h"

typedef const char* string;

class Shader
{
public:
	Shader(std::string path);
	Shader(std::string name, std::string path);
	virtual ~Shader() {};

	void use();
	GLint findProperty(string prop);
	bool hasProperty(string prop);
	GLuint get_Program();
private:
	GLuint m_ProgramID;
	void InitShader(std::string path);
};