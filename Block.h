#pragma once
#include <vector>
#include<glm/glm.hpp>
#include "Vertex.h"

enum BlockType {
	BlockType_Air,
	BlockType_Grass,
	BlockType_Dirt,
	BlockType_Stone,
};

class Block
{
public:
	static std::vector<Vertex> GenerateUpdatedCubeData(int x, int y, int z);
	// Change blockType
	void changeBlockType(BlockType blockType);
	Block();
private:
	
	BlockType blocktype;
	bool isVisible;
};

