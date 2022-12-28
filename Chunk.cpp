#include "Chunk.h"

Chunk::Chunk(int chunksize) {
	CHUNKSIZE = chunksize; // Block *** blockList
	blockList = new Block * *[CHUNKSIZE];
	for (int i = 0; i < CHUNKSIZE; i++) {
		blockList[i] = new Block * [CHUNKSIZE];
		for (int j = 0; j < CHUNKSIZE; j++) {
			blockList[i][j] = new Block[CHUNKSIZE];
		}
	}
	GenerateChunk();
}

Chunk::~Chunk() {
	for (int i = 0; i < CHUNKSIZE; i++) {
		for (int j = 0; j < CHUNKSIZE; j++) {
			delete[] blockList[i][j];
		}
		delete[] blockList[i];
	}
	delete[] blockList;
}

void Chunk::GenerateChunk()
{	
	for (int i = 0; i < CHUNKSIZE; i++) {
		for (int j = 0; j < CHUNKSIZE; j++) {
			for (int k = 0; k < CHUNKSIZE; k++){
				double di = static_cast<double>(i), dj = static_cast<double>(j), dk = static_cast<double>(k);
				blockList[i][j][k] = Block(BlockType_Grass, di, dj, dk);
			}
		}
	}
	m_ChunkWorkedOn = true;
}

void Chunk::CheckNeighborsAndSetIfFaceShouldBeVisible() 
{
	for (int x = 0; x < CHUNKSIZE; x++) {
		for (int y = 0; y < CHUNKSIZE; y++) {
			for (int z = 0; z < CHUNKSIZE; z++) {
				if (blockList[x][y][z].ReturnBlockType() == BlockType_Air) {
					blockList[x][y][z].SetAllFaceToBoolValue(false);
				}else {
					// check top    x, y + 1, z 
					if (y + 1 < CHUNKSIZE && blockList[x][y + 1][z].ReturnBlockType() != BlockType_Air)
						blockList[x][y][z].SetFaceVisible(BlockFace_Top, false);
					else
						blockList[x][y][z].SetFaceVisible(BlockFace_Top, true);
					// check bottom x, y - 1, z 
					if (y - 1 >= 0 && blockList[x][y - 1][z].ReturnBlockType() != BlockType_Air) {
						blockList[x][y][z].SetFaceVisible(BlockFace_Bottom, false);
					}
					else
						blockList[x][y][z].SetFaceVisible(BlockFace_Bottom, true);
					// check front  x, y, z + 1
					if (z + 1 < CHUNKSIZE && blockList[x][y][z + 1].ReturnBlockType() != BlockType_Air)
						blockList[x][y][z].SetFaceVisible(BlockFace_Front, false);
					else
						blockList[x][y][z].SetFaceVisible(BlockFace_Front, true);
					// check back   x, y, z - 1 
					if (z - 1 >= 0 && blockList[x][y][z - 1].ReturnBlockType() != BlockType_Air)
						blockList[x][y][z].SetFaceVisible(BlockFace_Back, false);
					else
						blockList[x][y][z].SetFaceVisible(BlockFace_Back, true);
					// check left   x - 1, y, z 
					if (x - 1 >= 0 && blockList[x - 1][y][z].ReturnBlockType() != BlockType_Air)
						blockList[x][y][z].SetFaceVisible(BlockFace_Left, false);
					else
						blockList[x][y][z].SetFaceVisible(BlockFace_Left, true);
					// check right  x + 1, y, z 
					if (x + 1 < CHUNKSIZE && blockList[x + 1][y][z].ReturnBlockType() != BlockType_Air)
						blockList[x][y][z].SetFaceVisible(BlockFace_Right, false);
					else
						blockList[x][y][z].SetFaceVisible(BlockFace_Right, true);
				}
			}
		}
	}
}

std::vector<Vertex> Chunk::CreateChunkMesh() {
	// we can do a if check to see if any work has been done on this chunk
	// that way we don't have to recalculate any unnessary work

	if (m_ChunkWorkedOn) {
		CheckNeighborsAndSetIfFaceShouldBeVisible();
		m_ChunkWorkedOn = false;
	}
	std::vector<Vertex> output;
	for (int i = 0; i < CHUNKSIZE; i++) {
		for (int j = 0; j < CHUNKSIZE; j++) {
			for (int k = 0; k < CHUNKSIZE; k++) {
				// if block is visible
				if (blockList[i][j][k].GetVisible()) {
					double di = static_cast<double>(i), dj = static_cast<double>(j), dk = static_cast<double>(k);
					std::vector<Vertex> updatedCubeData = Chunk::GenerateUpdatedCubeData(blockList[i][j][k]);
					output.insert(output.end(), updatedCubeData.begin(), updatedCubeData.end());
				}
			}
		}
	}
	return output;
}

void Chunk::setChunkWorkedOn(bool val)
{
	m_ChunkWorkedOn = val;
}

bool Chunk::getChunkWorkedOnBoolVal()
{
	return m_ChunkWorkedOn;
}

/*
	Chunk Management will take player position and generate chunks around the position.
*/
 
const std::vector<Vertex> Chunk::cubeData = {
	// top
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),

	// bottom
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),

	// front
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),

	// back
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),

	// left
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),

	// right
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
};

std::vector<Vertex> Chunk::GenerateUpdatedCubeData(Block block) {
    // check the neighbors and pass the face here
	// order: top bottom front back left right
	std::vector<Vertex> updatedCube;
	int faceCounter = 0; // 0 -> 5
	for (int point = 0; point < cubeData.size(); point = point + 6)
	{
		// we are at the start of the new face and we are checking if that face should be visible
		if (block.ReturnFaceVisibleBool(static_cast<BlockFace>(faceCounter)))
		{
			// Iterating over a face to push data onto our return container
			for (int currPoint = point; currPoint < point + 6; currPoint++) {
				const glm::vec3 pos = cubeData[currPoint].Position;
				const Position cubePosition = block.ReturnPosition();
				int x = cubePosition.x, y = cubePosition.y, z = cubePosition.z;
				// texture should take as values the face as well as id but the id is internal 
				Vertex v(glm::vec3(pos.x + x, pos.y + y, pos.z + z), AtlasTexture::GetCorrectedPixelCoordGivenIndexAndOldCoord(cubeData[currPoint].Texture, Block::ReturnFaceTexIndex(block.ReturnBlockType(), static_cast<BlockFace>(faceCounter))));
				updatedCube.push_back(v);
			}
		}
		// Regardless of which ever case we move onto the next face
		faceCounter++;
	}

	return updatedCube;
}
