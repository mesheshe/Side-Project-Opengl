#version 330 core
out vec4 FragColor;

void main(){
	vec3 color1 = vec3(1.0f, 1.0f, 0.0f);
	vec3 color2 = vec3(1.0f, 0.0f, 1.0f);
	vec3 color = vec3(0.0f) + mix(color1, color2, 0.5f);
	FragColor = vec4(color, 1.0f);
}