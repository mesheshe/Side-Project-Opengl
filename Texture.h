#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <stb_image/stb_image.h>
class Texture
{
private:
	std::string filePath;
	// width and height refer to image width and height
	// nrChannels refer to number of channels
	int width, height, numChannels;
	GLuint texID;
	unsigned char* imageData;
	void loadImage();
public:
	Texture(std::string path);
	~Texture();
	void Bind(unsigned int slot = 0);
	void Unbind();
};

