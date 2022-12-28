#include "Mesh.h"

void Mesh::Draw(Shader& s)
{
	if (m_Draw)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(Vertex));
		glBindVertexArray(0);
	}
}

void Mesh::SetUpMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Texture));

	// unbinding VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// unbinding VAO
	glBindVertexArray(0);

	
}

Mesh::Mesh(std::vector<Vertex> vertices)
{
	// maybe include indicies
	this->vertices = vertices;
	if (vertices.size() > 0)
		SetUpMesh();
	else
		m_Draw = false;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}