#pragma once
#include "Texture.h"
#include "Shader.h"
#include <string>

class AtlasTexture : private Texture
{
public:
	AtlasTexture(std::string filePath, float numOfRows, float numOfColumns);
	static glm::vec2 GetCorrectedPixelCoordGivenIndexAndOldCoord(glm::vec2 coord, glm::vec2 index);
	void Bind();
private:
	static float m_NumOfRows;
	static float m_NumOfColumns;
};

