#include "Texture.h"

Texture::Texture(std::string path) {
	filePath = path;
	loadImage();

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	if (imageData)
		stbi_image_free(imageData);

}

Texture::Texture()
{
	filePath = "";
	width = height = numChannels = -1;
	texID = 0;
	imageData = NULL;
}

void Texture::loadImage() {
	
	stbi_set_flip_vertically_on_load(false);

	imageData = stbi_load(filePath.c_str(), &width, &height, &numChannels, 4);

	if (imageData == NULL) {
		std::cerr << "ERROR::File not loaded " << stbi_failure_reason() << std::endl;
		return;
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &texID);
}

void Texture::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getHeight()
{
	return height;
}

int Texture::getWidth()
{
	return width;
}
