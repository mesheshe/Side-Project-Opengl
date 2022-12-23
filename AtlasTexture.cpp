#include "AtlasTexture.h"

AtlasTexture::AtlasTexture(std::string filePath, int numOfRows)
{
	Texture(filePath.c_str());
	m_NumOfRows = numOfRows;
}
