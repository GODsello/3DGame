#version 330 core

out vec4 FragColor;

in vec3 FragPos;

uniform vec3 gameObjectColor;

void main()
{
	FragColor = vec4(gameObjectColor, 1.0);
}