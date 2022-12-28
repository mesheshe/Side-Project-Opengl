#include "Block.h"

Block::Block(BlockType blockType, double x, double y, double z)
{
	m_BlockType = blockType;
	m_Position = { x, y, z };
	if (blockType != BlockType_Air)
		SetAllFaceToBoolValue(true);
}

bool Block::ReturnFaceVisibleBool(BlockFace bFace)
{
	return m_FacesVisible[bFace];
}

void Block::SetFaceVisible(BlockFace bFace, bool boolValue)
{
	m_FacesVisible[bFace] = boolValue;
	// isVisible will be set in this function only. 
	// first checks if the current input is true or false
	if (boolValue == false) {
		for (int i = 0; i < 6; i++) {
			// this checks if any of the face are visible and if so
			// we return right away. No need to set isVisible to true,
			// since already done so
			if (m_FacesVisible[i]) {
				return;
			}
		}
		m_IsVisible = false;
	}
	else {
		m_IsVisible = true;
	}
}

Position Block::ReturnPosition()
{
	return m_Position;
}

BlockType Block::ReturnBlockType()
{
	return m_BlockType;
}

void Block::SetAllFaceToBoolValue(bool value){
	for (int i = 0; i < 6; i++) {
		SetFaceVisible(static_cast<BlockFace>(i), value);
	}
}


glm::vec2 Block::ReturnFaceTexIndex(BlockType bType, BlockFace bFace)
{
	switch (bType) {
	case BlockType_Dirt:
		return glm::vec2(7.0f, 5.0f);
	case BlockType_Stone:
		return glm::vec2(3.0f, 4.0f);
	case BlockType_Grass:
		if (bFace == BlockFace_Top)
			return glm::vec2(8.0f, 0.0f);
		else if (bFace == BlockFace_Bottom)
			return glm::vec2(7.0f, 5.0f);
		else // BlockFace_Right
			return glm::vec2(7.0f, 4.0f);
	default: // BlockType_Brick
		return glm::vec2(0.0f, 0.0f);
	};
}


bool Block::GetVisible() {
	return m_IsVisible;
}
