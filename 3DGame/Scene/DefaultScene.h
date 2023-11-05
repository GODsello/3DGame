#pragma once

#include <vector>

#include "Scene.h"
#include "../ECS/GameObject.h"
#include "../Mesh/mesh.h";


class DefaultScene : public Scene
{
public:
	DefaultScene(unsigned int id, Renderer* renderer) : Scene(id, renderer){}

	void LoadScene()
	{
		this->mainShader = new Shader("Assets/Shaders/shader.vert", "Assets/Shaders/shader.frag");
		this->mainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

		Vertex vTL = { glm::vec3(-1.0f, 0.0f, 1.0f) };
		Vertex vTR = { glm::vec3(1.0f, 0.0f, 1.0f) };
		Vertex vBR = { glm::vec3(1.0f, 0.0f, -1.0f) };
		Vertex vBL = { glm::vec3(-1.0f, 0.0f, -1.0f) };

		std::vector<Vertex> vertices = { vTL, vTR, vBR, vBL };
		std::vector<unsigned int> indices = { 0, 1, 3, 3, 2, 1 };

		Mesh* m = new Mesh(vertices, indices);

		GameObject* g = new GameObject("ground");
		g->AddMesh(m);

		this->gameObjects.push_back(g);
	}
};