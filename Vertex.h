#pragma once
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 Position;
	// glm::vec3 Normal 
	glm::vec2 Texture;
	
	Vertex(glm::vec3 pos, glm::vec2 tex)
	{
		Position = pos;
		Texture = tex;
	}
};


