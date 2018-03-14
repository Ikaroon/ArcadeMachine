#pragma once
#include "Shader.h"
#include "Texture.h"

class Material
{
public:

	static Material* SPRITE_MATERIAL;
	static Material* UI_MATERIAL;
	static Material* STANDARD_MATERIAL;

	explicit Material(std::string name, Shader* shader);
	Material(Shader* shader);

	virtual ~Material();

	void setActive();
	void setMVP(glm::mat4 view, glm::mat4 proj, glm::mat4 model);
	void setTexture(std::string name, Texture* texture);
	void setVector(std::string name, glm::vec2 vector);
	void setVector(std::string name, glm::vec3 vector);
	void setInt(std::string name, int value);

private:
	Shader* m_Shader;
	std::map<std::string, Texture*> m_Textures;
	std::map<std::string, glm::vec2> m_Vector2s;
	std::map<std::string, glm::vec3> m_Vector3s;
	std::map<std::string, int> m_Ints;
};

//Material* Material::SPRITE_MATERIAL = new Material(NULL);
//Material* Material::UI_MATERIAL = new Material(NULL);
//Material* Material::STANDARD_MATERIAL = new Material(NULL);