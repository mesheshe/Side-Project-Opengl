#version 460 core

out vec4 FragColor;

in vec2 TexCoord0;

uniform sampler2D aSampler;

void main(){
	FragColor =  texture(aSampler, TexCoord0);
}