#pragma once
#include <vector>
#include <glm.hpp>

namespace OBJLoader
{
	bool load(const char * path, std::vector <glm::vec3> & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals)
	{
		FILE * file = fopen(path, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			return false;
		}
	}

};