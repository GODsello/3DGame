#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../renderer.h"
#include "../ecs/ecs.h"
#include "../camera/camera.h"
#include "../shader.h"
#include "../input/mouselistener.h"
#include "../input/keylistener.h"
#include "../ui/ui.h"
#include "../objects/light.h"

class Scene
{
public:
	Scene(unsigned int id, Renderer* renderer)
	{
		this->id = id;
		this->p_renderer = renderer;
		this->p_main_camera = nullptr;
		this->p_main_shader = nullptr;
		this->p_ui = nullptr;
		this->directional_light.direction = glm::vec3(0.0f, -1.0f, 0.0f);
		this->directional_light.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		this->directional_light.diffuse = glm::vec3(0.1f, 0.1f, 0.1f);
		this->directional_light.specular = glm::vec3(0.1f, 0.1f, 0.1f);
	}

	~Scene()
	{
		DownloadScene();
	}

	virtual void LoadScene() = 0;

	void StartScene()
	{
		for (GameObject* g : game_objects)
		{
			g->Start();
		}
	}

	void UpdateScene(float dt)
	{
		for (GameObject* g : game_objects)
		{
			g->Update(dt);
		}
	}

	void DownloadScene()
	{
		for (GameObject* g : game_objects)
		{
			delete g;
		}
		
		game_objects.clear();
		delete p_ui;
		p_ui = nullptr;
		delete p_main_camera;
		p_main_camera = nullptr;
		delete p_main_shader;
		p_main_shader = nullptr;
	}

	void RenderScene()
	{
		p_main_shader->Use();
		
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(p_main_camera->zoom), 
			static_cast<float>(Renderer::SCR_WIDTH) / static_cast<float>(Renderer::SCR_HEIGHT),
			0.1f, 100.0f);
		glm::mat4 view = p_main_camera->GetViewMatrix();
		p_main_shader->SetMat4("projection", projection);
		p_main_shader->SetMat4("view", view);

		p_main_shader->SetVec3("viewPos", p_main_camera->position);

		p_main_shader->SetVec3("dirLight.direction", directional_light.direction);
		p_main_shader->SetVec3("dirLight.ambient", directional_light.ambient);
		p_main_shader->SetVec3("dirLight.diffuse", directional_light.diffuse);
		p_main_shader->SetVec3("dirLight.specular", directional_light.specular);

		for (GameObject* g : game_objects)
		{
			g->Render(p_main_shader);
		}

		if (p_ui)
		{
			p_ui->RenderUI(p_renderer);
		}
	}

	void ProcessInput()
	{
		if (KeyListener::IsPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(p_renderer->p_window, true);
		}
	}

	Camera* GetMainCamera() { return p_main_camera; }

	std::vector<GameObject*>* GetSceneGameObjects() { return &game_objects; }

	void AddGameObject(GameObject* p_go)
	{
		this->game_objects.push_back(p_go);
		for (GameObject* p_g : p_go->GetChildGameObjects())
		{
			AddGameObject(p_g);
		}
	}

	void ClearGameObjects()
	{
		for (int i = this->game_objects.size()-1; i >= 0; i--)
		{
			if (this->game_objects[i]->GetShouldRemove())
			{
				delete this->game_objects[i];
				this->game_objects.erase(this->game_objects.begin() + i, this->game_objects.begin() + i + 1);
			}
		}
	}

protected:
	unsigned int id;

	std::vector<GameObject*> game_objects;
	Camera *p_main_camera;
	Shader *p_main_shader;
	UI *p_ui;
	DirLight directional_light;

	Renderer* p_renderer;
};