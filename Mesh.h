#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Vertex.h"
 

class Mesh
{
private:
	GLuint VAO, VBO;
 
public:
	std::vector<Vertex> vertices;

	Mesh(std::vector<Vertex> vertices);
	~Mesh();
	void Draw(Shader &s);
	void SetUpMesh();
};
