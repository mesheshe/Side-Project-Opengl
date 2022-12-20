#version 460 core

out vec4 FragColor;

in vec2 TexCoord0;

uniform sampler2D aSampler;

void main(){
	vec3 color1 = vec3(1.0f, 1.0f, 0.0f);
	vec3 color2 = vec3(1.0f, 0.0f, 1.0f);
	vec3 color = vec3(0.0f) + mix(color1, color2, 0.5f);
	FragColor =  texture(aSampler, TexCoord0) * vec4(color, 1.0f);
}