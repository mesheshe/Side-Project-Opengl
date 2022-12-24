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

// proof of concept
std::vector<Vertex> Chunk::GenerateCube()
{
	std::vector<Vertex> output;
	std::vector<Vertex> updatedCubeData = Chunk::GenerateUpdatedCubeData(0, 0, 0);
	output.insert(output.end(), updatedCubeData.begin(), updatedCubeData.end());
	return output;
	/*
	const int halfCHUNKSIZE = CHUNKSIZE / 2;
	for (int i = -halfCHUNKSIZE; i < halfCHUNKSIZE; i++){
		for (int j = -halfCHUNKSIZE; j < halfCHUNKSIZE; j++){
			for (int k = -halfCHUNKSIZE; k < halfCHUNKSIZE; k++){
				std::vector<Vertex> updatedCubeData = Chunk::GenerateUpdatedCubeData(i, j, k);
				output.insert(output.end(), updatedCubeData.begin(), updatedCubeData.end());
			}
		}
	}
	return output;
	*/
}
// proof of concept
std::vector<Vertex> Chunk::GenerateSphere()
{
	std::vector<Vertex> output;
	const int halfCHUNKSIZE = CHUNKSIZE / 2;
	for (int i = -halfCHUNKSIZE; i < halfCHUNKSIZE; i++){
		for (int j = -halfCHUNKSIZE; j < halfCHUNKSIZE; j++){
			for (int k = -halfCHUNKSIZE; k < halfCHUNKSIZE; k++) {
				// generating cube, squared therefore only comparing the actual values
				if (pow(i, 2) + pow(j, 2) + pow(k, 2) <= pow(halfCHUNKSIZE, 2)){
					std::vector<Vertex> updatedCubeData = Chunk::GenerateUpdatedCubeData(i, j, k);
					output.insert(output.end(), updatedCubeData.begin(), updatedCubeData.end());
				}
			}
		}
	}
	return output;
}

std::vector<Vertex> Chunk::GeneratePyramid()
{
	std::vector<Vertex> output;
	const int halfCHUNKSIZE = CHUNKSIZE / 2; // 5
	for (int height = 0; height <= halfCHUNKSIZE; height++) {
		// we want the base of the pyramid at height = 0. With that in mind
		// and knowing the max height of the pyramid we can simply accomplish
		// that by subtracting the maxHeight  possible by height. Sort of like
		// an inverse relationship
		const int length = halfCHUNKSIZE - height;
		for (int i = -halfCHUNKSIZE; i <= halfCHUNKSIZE; i++) {
			for (int k = -halfCHUNKSIZE; k <= halfCHUNKSIZE; k++) {
				// generating cube; as you go from height = -5 to 0, you are 
				// similarly generating a flat square of specified length
				// here the abs(i) == abs(length and ab(k) == abs(length) ensures that we are only considering the edge
				if ((abs(i) == abs(length) && abs(k) <= abs(length)) || (abs(k) == abs(length) && abs(i) <= abs(length)))	{
					std::vector<Vertex> updatedCubeData = Chunk::GenerateUpdatedCubeData(i, height , k);
					output.insert(output.end(), updatedCubeData.begin(), updatedCubeData.end());
				}
			}
		}
	}
	return output;
}


std::vector<Vertex> Chunk::GenerateFloor()
{	

	std::vector<Vertex> output;

	return output;
}

/*
	I want to create a chunk manager where it will basically manage everything that happens inside the chunk. This chunk manager will be an internal class used mainly
	by the Chunk Class. One of the methods that will be available is specifiying whether something should be visible or not.
*/

const std::vector<Vertex> Chunk::cubeData = {
	// back
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
	// front
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	// left
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	// right
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
	// bottom
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	// top
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
	Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f))
};

std::vector<Vertex> Chunk::GenerateUpdatedCubeData(int x, int y, int z) {
	std::vector<Vertex> updatedCube;
	for (int point = 0; point < cubeData.size(); point++) {
		const glm::vec3 pos = cubeData[point].Position;
		Vertex v(glm::vec3(pos.x + x, pos.y + y, pos.z + z), AtlasTexture::GetCorrectedPixelCoordGivenIndexAndOldCoord(cubeData[point].Texture, glm::vec2(0.0f, 0.0f)));
		updatedCube.push_back(v);
	}
	return updatedCube;
}
