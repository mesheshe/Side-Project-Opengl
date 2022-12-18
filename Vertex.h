#pragma once
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 Position;
	// glm::vec3 Normal 
	// glm::vecX texture
	
	Vertex(glm::vec3 pos)
	{
		Position = pos;
	}
};


