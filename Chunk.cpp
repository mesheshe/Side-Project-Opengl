#include "Chunk.h"

Chunk::Chunk(int chunksize) {
	CHUNKSIZE = chunksize;
}

// proof of concept
std::vector<Vertex> Chunk::GenerateCube()
{
	std::vector<Vertex> output;
	const int halfCHUNKSIZE = CHUNKSIZE / 2;
	for (int i = -halfCHUNKSIZE; i < halfCHUNKSIZE; i++){
		for (int j = -halfCHUNKSIZE; j < halfCHUNKSIZE; j++){
			for (int k = -halfCHUNKSIZE; k < halfCHUNKSIZE; k++){
				std::vector<Vertex> updatedCubeData = GenerateUpdatedCubeData(i, j, k);
				output.insert(output.end(), updatedCubeData.begin(), updatedCubeData.end());
			}
		}
	}
	return output;
}
// proof of concept
std::vector<Vertex> Chunk::GenerateSphere()
{
	std::vector<Vertex> output;
	const int halfCHUNKSIZE = CHUNKSIZE / 2;
	for (int i = -halfCHUNKSIZE; i < halfCHUNKSIZE; i++){
		for (int j = -halfCHUNKSIZE; j < halfCHUNKSIZE; j++){
			for (int k = -halfCHUNKSIZE; k < halfCHUNKSIZE; k++) {
				// generating cube
				if (pow(i, 2) + pow(j, 2) + pow(k, 2) <= pow(halfCHUNKSIZE, 2)){
					std::vector<Vertex> updatedCubeData = GenerateUpdatedCubeData(i, j, k);
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
	for (int height = 0; height != halfCHUNKSIZE; height++) {
		for (int i = -halfCHUNKSIZE; i <= halfCHUNKSIZE; i++) {
			for (int k = -halfCHUNKSIZE; k <= halfCHUNKSIZE; k++) {
				// generating cube
				if (abs(i) <= height && abs(k) <= height)	{
					std::vector<Vertex> updatedCubeData = GenerateUpdatedCubeData(i, height, k);
					output.insert(output.end(), updatedCubeData.begin(), updatedCubeData.end());

				}
			}
		}
	}
	return output;
}

// why does variable have to be i, j, k and not x, y, z. There is a bug involved
std::vector<Vertex> Chunk::GenerateUpdatedCubeData(int i, int j, int k) {
	std::vector<Vertex> updatedCube;
	for (int z = 0; z < cubeData.size(); z++) {
		const glm::vec3 pos = cubeData[z].Position;
		Vertex v(glm::vec3(pos.x + i, pos.y + j, pos.z + k));
		updatedCube.push_back(v);
	}
	return updatedCube;
}


