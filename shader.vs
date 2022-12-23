#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TexCoord;

out vec2 TexCoord0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float numOfRows;
uniform vec2 offset;

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0f);
	TexCoord0 = TexCoord / numOfRows + offset;
}