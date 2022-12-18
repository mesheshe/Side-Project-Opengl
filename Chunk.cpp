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
				for (int z = 0; z < cubeData.size(); z++)
				{
					glm::vec3 pos = cubeData[z].Position;  // extracting the data
					Vertex v(glm::vec3(pos.x + i, pos.y + j, pos.z + k)); // changing the data
					output.push_back(v);   // adding data to output 
				}
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
				for (int k = -halfCHUNKSIZE; k < halfCHUNKSIZE; k++) {
					for (int z = 0; z < cubeData.size(); z++) {
						glm::vec3 pos = cubeData[z].Position;
						if (pow(pos.x + i, 2) + pow(pos.y + j, 2) + pow(pos.z + k, 2) <= pow(halfCHUNKSIZE, 2)) {
							Vertex v(glm::vec3(pos.x + i, pos.y + j, pos.z + k));
							output.push_back(v);
						}
					}
				}
			}
		}
	}
	return output;
}