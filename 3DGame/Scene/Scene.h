#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../renderer.h"
#include "../ECS/ECS.h"
#include "../Camera/camera.h"
#include "../shader.h"
#include "../Input/MouseListener.h"
#include "../Input/KeyListener.h"

class Scene
{
public:
	Scene(unsigned int id, Renderer* renderer)
	{
		this->id = id;
		this->renderer = renderer;
		this->mainCamera = nullptr;
		this->mainShader = nullptr;
	}

	~Scene()
	{
		DownloadScene();
	}

	virtual void LoadScene() = 0;

	void StartScene()
	{
		for (GameObject* g : gameObjects)
		{
			g->Start();
		}
	}

	void UpdateScene(float dt)
	{
		for (GameObject* g : gameObjects)
		{
			g->Update(dt);
		}
	}

	void DownloadScene()
	{
		for (GameObject* g : gameObjects)
		{
			delete g;
		}

		gameObjects.clear();
		delete mainCamera;
		mainCamera = nullptr;
		delete mainShader;
		mainShader = nullptr;
	}

	void RenderScene()
	{
		mainShader->use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(mainCamera->Zoom), 
			static_cast<float>(Renderer::SCR_WIDTH) / static_cast<float>(Renderer::SCR_HEIGHT),
			0.1f, 100.0f);
		glm::mat4 view = mainCamera->GetViewMatrix();
		mainShader->setMat4("projection", projection);
		mainShader->setMat4("view", view);

		for (GameObject* g : gameObjects)
		{
			g->Render(mainShader);
		}
	}

	void ProcessInput()
	{
		if (KeyListener::isPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(renderer->window, true);
		}
	}

	Camera* GetMainCamera() { return mainCamera; }

	std::vector<GameObject*>* GetSceneGameObjects() { return &gameObjects; }

protected:
	unsigned int id;

	std::vector<GameObject*> gameObjects;
	Camera* mainCamera;
	Shader* mainShader;

	Renderer* renderer;
};