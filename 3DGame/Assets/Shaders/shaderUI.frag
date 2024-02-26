#version 330 core

out vec4 FragColor;

in vec3 FragPos;

uniform vec3 uiComponentColor;

void main()
{
	FragColor = vec4(uiComponentColor, 1.0);
}