#pragma once

#include <unordered_map>

#include "../camera/camera.h"
#include "../shader.h"
#include "../renderer.h"
#include "components/uicomponent.h"

class UI
{
public:
	UI(const char* vertex_path, const char* fragment_path)
	{
		p_ui_camera = new Camera();
		p_ui_shader = new Shader(vertex_path, fragment_path);
	}

	~UI()
	{
		delete p_ui_camera;
		p_ui_camera = nullptr;
		delete p_ui_shader;
		p_ui_shader = nullptr;
	}

	void AddUIComponent(std::string id, UIComponent *p_ui_component)
	{
		p_ui_component->SetShader(p_ui_shader);
		ui_components[id] = p_ui_component;
	}

	UIComponent* GetUIComponent(std::string id)
	{
		return ui_components[id];
	}

	void RenderUI(Renderer *p_renderer)
	{
		p_ui_shader->Use();

		// view/projection transformations
		glm::mat4 projection = glm::ortho(0.0f, (float)p_renderer->SCR_WIDTH, 0.f, (float)p_renderer->SCR_HEIGHT, 0.1f, 10.0f);
		//glm::mat4 view = p_ui_camera->GetViewMatrix();
		p_ui_shader->SetMat4("projection", projection);
		//p_ui_shader->SetMat4("view", view);

		for (auto c = ui_components.begin(); c != ui_components.end(); c++)
		{
			c->second->Render();
		}
	}

private:
	Camera *p_ui_camera;
	Shader *p_ui_shader;

	std::unordered_map<std::string, UIComponent*> ui_components;
};