#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>

class Shader
{
private:

	GLuint ID;

	const static int SHADER_COUNT = 2;

	static void checkError(GLuint shader, GLint flag, bool isProgram, const std::string& errorMsg);

	static GLuint createShader(const std::string& shaderText, GLenum shaderType);

	static std::string readFromFile(const std::string& nfileName);

public:

	Shader(const std::string& shaderFileName);

	~Shader();

	Shader(const std::string vertexFileName, const std::string& fragmentFileName);

	void use() const;

	void setMat4(const std::string& name, const glm::mat4& value) const;
	
	void setInteger(const std::string& name, const int value) const;
};

