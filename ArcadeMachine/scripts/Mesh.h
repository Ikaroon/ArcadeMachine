#pragma once
#include "stdafx.h"
#include <vector>
#include "glm.hpp"

class Mesh
{
public:
	Mesh(std::string name);
	virtual ~Mesh() {};

	void set_Vertices(std::vector<glm::vec3> vertices);
	void set_UVs(std::vector<glm::vec2> uvs);
	void set_Normals(std::vector<glm::vec3> normals);

	void calculateNormals();

	void draw();

private:
	void calculateGLData();

	std::vector<unsigned short> m_IndicesBufferData;
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec2> m_Uvs;
	std::vector<glm::vec3> m_Normals;
	GLuint m_VertexArrayID = NULL;
	GLuint m_VertexBufferID = NULL;
};