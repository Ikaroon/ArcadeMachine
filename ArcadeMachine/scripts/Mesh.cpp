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

void Mesh::set_Colors(std::vector<glm::vec3> colors)
{
	m_VertexColors = colors;
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

	if (m_VertexBufferID != NULL)
	{
		// 1st attribute buffer : vertices
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
	}

	if (m_VertexColorBufferID)
	{
		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexColorBufferID);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,					// size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
	}

	if (m_UvBufferID)
	{
		// 3nd attribute buffer : uvs
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_UvBufferID);
		glVertexAttribPointer(
			2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,					// size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
	}

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

	// Disable buffers
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Mesh::calculateGLData()
{
	// Vertices
	if (m_Vertices.size() > 0)
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

	// Colors
	if (m_VertexColors.size() > 0)
	{
		if (m_VertexColorArrayID == NULL)
		{
			glGenVertexArrays(1, &m_VertexColorArrayID);
		}
		glBindVertexArray(m_VertexColorArrayID);

		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		if (m_VertexColorBufferID == NULL)
		{
			glGenBuffers(1, &m_VertexColorBufferID);
		}
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexColorBufferID);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_VertexColors.size(), &m_VertexColors[0], GL_STATIC_DRAW);
	}

	// Uvs
	if (m_Uvs.size() > 0)
	{
		if (m_UvArrayID == NULL)
		{
			glGenVertexArrays(1, &m_UvArrayID);
		}
		glBindVertexArray(m_UvArrayID);

		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		if (m_UvBufferID == NULL)
		{
			glGenBuffers(1, &m_UvBufferID);
		}
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_UvBufferID);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_Uvs.size(), &m_Uvs[0], GL_STATIC_DRAW);
	}

}
