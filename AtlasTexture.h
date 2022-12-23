#pragma once
#include "Texture.h"
#include <string>

class AtlasTexture : private Texture
{
public:
	AtlasTexture(std::string filePath, int numOfRows);
private:
	int m_NumOfRows;
};

