#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Chunk.h"
#include "AtlasTexture.h"
/* Next order of tasks
*	Mouse control just like in any FP game // Done
*	Generate chunks -> create floor -> collision detection
*	Optimize by only showing the viewable blocks
*	Perhaps look into the greedy algorithm
*	encapsulating // gettig there
*	save state of chunks
*	Start logging
*	Add Physics
*	Textures pls
*/


#define CHUNKSIZE 10


glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

float lastFrame = 0.0f;
float deltaTime;
float lastMousePosX = 400, lastMousePosY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;

bool outline = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
std::vector<Vertex> returnVectorFromFloatArrayContaingOnlyPositionVec(const float data[], int length);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft", NULL, NULL);

	//Error checking to see if window creation is sucessfull

	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << "Hello World" << std::endl;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Creating Shader Program
	Shader shader("shader");
	
	//Chunk 
	Chunk chunk(CHUNKSIZE);
	
	// Texture
	AtlasTexture tex("..\\..\\..\\\Downloads\\voxel-pack\\Spritesheets\\spritesheet_tiles.png", 9.0f, 10.0f);
	// defining the buffer that will send data and how to interpret it to the GPU
	Mesh mesh(chunk.CreateChunkMesh());
	
	shader.use();
	shader.setInteger("aSampler", 0);
	
	while (!glfwWindowShouldClose(window)) {
		// input
		const float currFrame = static_cast<float>(glfwGetTime());
		deltaTime = currFrame - lastFrame;
		lastFrame = currFrame;

		processInput(window);

		if (outline)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		std::cout << glm::to_string(cameraPosition) << " " << glm::to_string(cameraFront) << " " << glm::to_string(cameraUp) << " Pitch: " << pitch << " Yaw: " << yaw << std::endl;
		// update
		glClearColor(0.2f, 0.93f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tex.Bind();

		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
		view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

		shader.setMat4("view", view);
		shader.setMat4("proj", proj);
		shader.setMat4("model", model);

		// render
		mesh.Draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int height, int width)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	const float cameraSpeed = 2.5 * static_cast<float>(deltaTime);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPosition += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		outline = !outline;		
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// raw mouse position
	float xPos = (float)xpos;
	float yPos = (float)ypos;

	// initially we set lastMousePosX and lastMousePosY = 0 and so we are setting
	// it to the true value now
	if (firstMouse)
	{
		lastMousePosX = xPos;
		lastMousePosY = yPos;
		firstMouse = false;
	}

	// this will be how much needs to be added to pitch and yaw. Pitch refers to y while yaw refers to x
	float xoffset = xPos - lastMousePosX;
	float yoffset = lastMousePosY - yPos; // y-coordinates are flipped


	// saving the current mouse positions for the next calculations
	lastMousePosX = xPos;
	lastMousePosY = yPos;

	// controls how sensitive is the mouse
	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// screen will get flipped if we get passed these values
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// preventing from going past the limit of a float
	if (yaw >= 360.0f || yaw < -360.0f)
		yaw = 0;

	glm::vec3 direction = glm::vec3(1);

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	// recalculate cameraUp
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));

}

