#include "Chunk.h"

Chunk::Chunk(int chunksize) {
	CHUNKSIZE = chunksize;
}

// proof of concept
std::vector<Vertex> Chunk::GenerateCube()
{
	std::vector<Vertex> output;
	for (int i = 0; i < CHUNKSIZE; i++){
		for (int j = 0; j < CHUNKSIZE; j++){
			for (int k = 0; k < CHUNKSIZE; k++){
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

	return output;
}