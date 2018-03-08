#include "Mesh.h"
#include "MeshManager.h"

Mesh::Mesh(std::string name)
{
	MeshManager::addMesh(name, this);
}

void Mesh::set_Vertices(std::vector<glm::vec3> vertices)
{
	m_Vertices = vertices;
	calculateGLData();
}

void Mesh::set_UVs(std::vector<glm::vec2> uvs)
{
	m_Uvs = uvs;
	calculateGLData();
}

void Mesh::set_Normals(std::vector<glm::vec3> normals)
{
	m_Normals = normals;
	calculateGLData();
}

void Mesh::calculateNormals()
{
	//TODO: recalc the normals
	calculateGLData();
}

void Mesh::draw()
{
	if (m_VertexBufferID == NULL)
	{
		calculateGLData();
		return;
	}

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,					// size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void Mesh::calculateGLData()
{
	if (m_VertexArrayID == NULL)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}
	glBindVertexArray(m_VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	if (m_VertexBufferID == NULL)
	{
		glGenBuffers(1, &m_VertexBufferID);
	}
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

}
