#pragma once
#include <vector>
#include "Vertex.h"
#include "Block.h"
#include "AtlasTexture.h"

class Chunk
{
	// chunk will generate a mesh of voxels. 
	// generate unique shapes given a function x**2 + y**2 = r**2
	// we want save the state of chunks, whether to make them disappear or not
	// we need an array that holds position, eventually it will be a struct that holds position texture type and etc.
	// dont be afraid to try stuff, it is ok to not be right
private:
	int CHUNKSIZE;
	Block *** blockList; 
	// abstract this into a class called cube
	
	std::vector<Vertex> GenerateUpdatedCubeData(int x, int y, int z);
	static const std::vector<Vertex> cubeData;
	
public:
	Chunk(int chunksize);
	~Chunk();
	std::vector<Vertex> GenerateCube();
	std::vector<Vertex> GenerateSphere();
	std::vector<Vertex> GeneratePyramid();
	std::vector<Vertex> GenerateFloor();
	
};

