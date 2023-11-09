#pragma once

#include <vector>

#include "Scene.h"
#include "../ECS/ECS.h"
#include "../Mesh/mesh.h"
#include "../Objects/Player.h"
#include "../ECS/Components/Components.h"


class DefaultScene : public Scene
{
public:
	DefaultScene(unsigned int id, Renderer* renderer) : Scene(id, renderer){}

	void LoadScene()
	{
		this->mainShader = new Shader("Assets/Shaders/shader.vert", "Assets/Shaders/shader.frag");
		this->mainCamera = new Camera();
		
		//Ground
		//--------------------------------------------------------
		Vertex vTL = { glm::vec3(-0.5f, 0.0f, 0.5f) };
		Vertex vTR = { glm::vec3(0.5f, 0.0f, 0.5f) };
		Vertex vBR = { glm::vec3(0.5f, 0.0f, -0.5f) };
		Vertex vBL = { glm::vec3(-0.5f, 0.0f, -0.5f) };

		std::vector<Vertex> vertices = { vTL, vTR, vBR, vBL };
		std::vector<unsigned int> indices = { 0, 1, 3, 3, 2, 1 };

		Mesh* m = new Mesh(vertices, indices);

		GameObject* g = new GameObject("ground");
		g->AddMesh(m);

		g->GetTransform()->position = glm::vec3(0.0f, 0.0f, 0.0f);
		g->GetTransform()->scale = glm::vec3(20.0f, 2.0f, 20.0f);
		g->GetTransform()->color = glm::vec3(0.5f, 0.5f, 0.5f);
		Collider* collG = new Collider(COLLIDER_TYPE_BOX, glm::vec3(0.0f, 0.0f, -0.0f));
		collG->SetBoxParameters(-10.0f, 10.0f, -0.01f, 0.00f, -10.0f, 10.0f);
		g->addComponent(collG);
		this->gameObjects.push_back(g);

		//Wall
		//--------------------------------------------------------
		vTL = { glm::vec3(-0.5f, 0.5f, 0.0f) };
		vTR = { glm::vec3(0.5f, 0.5f, 0.0f) };
		vBR = { glm::vec3(0.5f, -0.5f, .0f) };
		vBL = { glm::vec3(-0.5f, -0.5f, 0.0f) };

		vertices = { vTL, vTR, vBR, vBL };
		indices = { 0, 1, 3, 3, 2, 1 };

		m = new Mesh(vertices, indices);

		g = new GameObject("wall");
		g->AddMesh(m);
		g->GetTransform()->position = glm::vec3(0.0f, 2.5f, 10.0f);
		g->GetTransform()->scale = glm::vec3(20.0f, 5.0f, 20.0f);
		g->GetTransform()->color = glm::vec3(1.0f, 0.0f, 0.0f);
		Collider* collW = new Collider(COLLIDER_TYPE_BOX, glm::vec3(0.0f, 2.5f, 10.0f));
		collW->SetBoxParameters(-10.0f, 10.0f, 0.0f, 5.0f, 9.99f, 10.01f);
		g->addComponent(collW);
		this->gameObjects.push_back(g);

		g = new GameObject("wall");
		g->AddMesh(m);
		g->GetTransform()->position = glm::vec3(0.0f, 2.5f, -10.0f);
		g->GetTransform()->scale = glm::vec3(20.0f, 5.0f, 20.0f);
		g->GetTransform()->color = glm::vec3(0.0f, 1.0f, 0.0f);
		collW = new Collider(COLLIDER_TYPE_BOX, glm::vec3(0.0f, 2.5f, -10.0f));
		collW->SetBoxParameters(-10.0f, 10.0f, 0.0f, 5.0f, -10.01f, -9.99f);
		g->addComponent(collW);
		this->gameObjects.push_back(g);

		//Player
		//--------------------------------------------------------
		Player* p = new Player("player", mainCamera);
		p->GetTransform()->position = glm::vec3(0.0f, 10.0f, 0.0f);
		Controller* c = new Controller(mainCamera);
		Physics* ph = new Physics();
		Collider* coll = new Collider(COLLIDER_TYPE_BOX, glm::vec3(0.0f, 10.0f, 0.0f));
		coll->SetBoxParameters(-0.5f, 0.5f, 10.0f, 11.75f, -0.5f, 0.5f);
		p->addComponent(coll);
		p->addComponent(c);
		p->addComponent(ph);
		this->gameObjects.push_back(p);
	}
};