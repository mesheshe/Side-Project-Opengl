#include "AtlasTexture.h"

// default values 
float AtlasTexture::m_NumOfRows = 1.0f;
float AtlasTexture::m_NumOfColumns = 1.0f;

AtlasTexture::AtlasTexture(std::string filePath, float numOfRows, float numOfColumns) : Texture(filePath.c_str()) {
	m_NumOfRows = numOfRows;
	m_NumOfColumns = numOfColumns;
}

glm::vec2 AtlasTexture::GetCorrectedPixelCoordGivenIndexAndOldCoord(glm::vec2 coord, glm::vec2 index)
{
	float x = index.x, y = m_NumOfColumns - 1 - index.y;
	glm::vec2 offset = glm::vec2(x / m_NumOfRows, y / m_NumOfColumns);
	glm::vec2 textureCoord = glm::vec2(coord.s/ m_NumOfRows, coord.t/ m_NumOfColumns) + offset;
	return textureCoord;
}

void AtlasTexture::Bind()
{
	Texture::Bind();
}


