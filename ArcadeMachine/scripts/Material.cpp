#include "Material.h"
#include "MaterialManager.h"

Material::Material(std::string name, Shader* shader)
{
	MaterialManager::addMaterial(name, this);
	m_Shader = shader;
}

Material::Material(Shader* shader)
{
	m_Shader = shader;
}

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
}

void Material::setMVP(glm::mat4 view, glm::mat4 proj, glm::mat4 model)
{
	// Get a handle for our "M" uniform
	GLuint MatrixID;/* = glGetUniformLocation(m_Shader->get_Program(), "_M");

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
	*/
	glm::mat4 mvp = proj * view * model;

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(m_Shader->get_Program(), "_MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}
