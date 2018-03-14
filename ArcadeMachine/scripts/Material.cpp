#include "Material.h"
#include "MaterialManager.h"

Material::Material(std::string name, Shader* shader)
{
	MaterialManager::addMaterial(name, this);
	m_Shader = shader;
}

Material::Material(Shader* shader) : Material("unnamed", shader) {}

Material::~Material()
{
	if (m_Shader != nullptr)
	{
		delete m_Shader;
	}
}

void Material::setActive()
{
	m_Shader->use();
	unsigned int texSampler = 0;
	for (auto const &texture : m_Textures)
	{
		glUniform1i(glGetUniformLocation(m_Shader->get_Program(), texture.first.c_str()), texSampler);
		glActiveTexture(GL_TEXTURE0 + texSampler);
		glBindTexture(GL_TEXTURE_2D, texture.second->get_ID());
		glBindSampler(0, 0);

		texSampler++;
	}
	for (auto const &vector : m_Vector3s)
	{
		GLuint vectorID = glGetUniformLocation(m_Shader->get_Program(), vector.first.c_str());
		glUniform3f(vectorID, vector.second.x, vector.second.y, vector.second.z);
	}
	for (auto const &vector : m_Vector2s)
	{
		GLuint vectorID = glGetUniformLocation(m_Shader->get_Program(), vector.first.c_str());
		glUniform2f(vectorID, vector.second.x, vector.second.y);
	}
	for (auto const &value : m_Ints)
	{
		GLuint intID = glGetUniformLocation(m_Shader->get_Program(), value.first.c_str());
		glUniform1i(intID, value.second);
	}
}

void Material::setMVP(glm::mat4 view, glm::mat4 proj, glm::mat4 model)
{
	// Get a handle for our "M" uniform
	GLuint MatrixID = glGetUniformLocation(m_Shader->get_Program(), "_M");

	// Send our transformation to the currently bound shader, in the "M" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &model[0][0]);

	// Get a handle for our "V" uniform
	MatrixID = glGetUniformLocation(m_Shader->get_Program(), "_V");

	// Send our transformation to the currently bound shader, in the "V" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &view[0][0]);

	// Get a handle for our "P" uniform
	MatrixID = glGetUniformLocation(m_Shader->get_Program(), "_P");

	// Send our transformation to the currently bound shader, in the "P" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &proj[0][0]);
	
	glm::mat4 mvp = proj * view * model;

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(m_Shader->get_Program(), "_MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void Material::setTexture(std::string name, Texture* texture)
{
	m_Textures[name] = texture;
}

void Material::setVector(std::string name, glm::vec2 vector)
{
	m_Vector2s[name] = vector;
}

void Material::setVector(std::string name, glm::vec3 vector)
{
	m_Vector3s[name] = vector;
}

void Material::setInt(std::string name, int value)
{
	m_Ints[name] = value;
}
