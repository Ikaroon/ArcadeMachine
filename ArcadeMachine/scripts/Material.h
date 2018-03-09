#pragma once
#include "Shader.h"
#include "Texture.h"

class Material
{
public:

	static Material* SPRITE_MATERIAL;
	static Material* UI_MATERIAL;
	static Material* STANDARD_MATERIAL;

	Material(Shader* shader);
	explicit Material(std::string name, Shader* shader);

	virtual ~Material();

	void setActive();
	void setMVP(glm::mat4 view, glm::mat4 proj, glm::mat4 model);
	void setTexture(std::string name, Texture* texture);
private:
	Shader* m_Shader;
	std::map<std::string, Texture*> m_Textures;
};

//Material* Material::SPRITE_MATERIAL = new Material(NULL);
//Material* Material::UI_MATERIAL = new Material(NULL);
//Material* Material::STANDARD_MATERIAL = new Material(NULL);