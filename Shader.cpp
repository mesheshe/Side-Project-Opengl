#include "Shader.h"

#pragma once
void Shader::checkError(GLuint shader, GLint flag, bool isProgram, const std::string& errorMsg)
{
	int success;
	char infoLog[512] = { 0 };

	if (!isProgram)
		glGetShaderiv(shader, flag, &success);
	else
		glGetProgramiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (!isProgram)
			glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		else
			glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);

		std::cerr << errorMsg << " : " << infoLog << std::endl;
	}
}


GLuint Shader::createShader(const std::string& shaderText, GLenum shaderType) {
	// refactoring data
	const GLchar* text = shaderText.c_str();
	// creating shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);
	// checking compilation status
	Shader::checkError(shader, GL_COMPILE_STATUS, false, "SHADER::COMPILATION_FAILED");
	return shader;
}



std::string Shader::readFromFile(const std::string& fileName) {
	// streaming class to read from file
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open()) {
		std::cerr << "ERROR::BAD_FILE" << std::endl;
		return "";
	}

	std::string output;
	std::string line;
	
	while (file.good()) {
		getline(file, line);
		output.append(line + "\n");
	}

	return output;
}

Shader::Shader(const std::string& shaderFileName) : Shader(shaderFileName + ".vs", shaderFileName + ".fs"){ }

Shader::Shader(const std::string vertexFileName, const std::string& fragmentFileName) {

	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	GLuint shaders[Shader::SHADER_COUNT];

	vertexShaderSource = readFromFile(vertexFileName);
	fragmentShaderSource = readFromFile(fragmentFileName);

	shaders[0] = createShader(vertexShaderSource, GL_VERTEX_SHADER);
	shaders[1] = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();

	for (int i = 0; i < Shader::SHADER_COUNT; i++)
	{
		glAttachShader(ID, shaders[i]);
	}

	glLinkProgram(ID);
	Shader::checkError(ID, GL_LINK_STATUS, true, "ERROR::PROGRAM::LINKING_FAILED");
	glValidateProgram(ID);
	Shader::checkError(ID, GL_VALIDATE_STATUS, true, "ERROR::PROGRAM::VALIDATION_FAILED");

	for (int i = 0; i < Shader::SHADER_COUNT; i++)
	{
		glDeleteShader(shaders[i]);
	}

}

Shader::~Shader() {

	glDeleteProgram(ID);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setMat4(const std::string& name, const glm::mat4 &value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shader::setInteger(const std::string& name, const int value) const {
	int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, value);
}