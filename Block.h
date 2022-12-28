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

// Now we can iterate through the face and decide whether
// to render that or not.
enum BlockFace {
	BlockFace_Top = 0,
	BlockFace_Bottom,
	BlockFace_Front,
	BlockFace_Back,
	BlockFace_Left,
	BlockFace_Right,
};

struct Position {
	double x;
	double y;
	double z;
};
class Block
{
public:
	Block(BlockType blockType, double x, double y, double z);
	Block() {};
	bool GetVisible();
	bool ReturnFaceVisibleBool(BlockFace bFace);
	void SetFaceVisible(BlockFace bFace, bool boolValue);
	Position ReturnPosition();
	BlockType ReturnBlockType();
	void SetAllFaceToBoolValue(bool value); 
	static glm::vec2 ReturnFaceTexIndex(BlockType bType, BlockFace bFace);

private:
	bool m_FacesVisible[6] = { false,false ,false, false, false, false };
	BlockType m_BlockType = BlockType_Air;
	bool m_IsVisible = false;
	Position m_Position = {0,0,0};
};

