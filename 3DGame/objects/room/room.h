#pragma once

#include "ground/ground.h"
#include "wall/wall.h"
#include "../../ecs/ecs.h"
#include "../light.h"

class Room : public GameObject
{
public:
	Room(glm::vec3 position,
		float x_width, float height, float z_width
	) : GameObject("room")
	{
		this->x_width = x_width;
		this->z_width = z_width;
		this->height = height;
		this->SetPosition(position);
		this->SetScale(glm::vec3(x_width, height, z_width));

		Ground* ground = new Ground(this,
			glm::vec3(0.0f),
			glm::vec3(0.0f),
			glm::vec3(x_width, 1.0f, z_width),
			glm::vec3(0.2f, 0.2f, 0.2f)
		);
		AddChild(ground);


		Wall* wall_0 = new Wall(this,
			glm::vec3(0.0f, height / 2.0f, z_width / 2.0f),
			glm::vec3(0.0f),
			glm::vec3(x_width, height, 0.01f),
			glm::vec3(1.0f, 0.0f, 0.0f)
		);
		AddChild(wall_0);

		Wall* wall_1 = new Wall(this,
			glm::vec3(0.0f, height / 2.0f, -z_width / 2.0f),
			glm::vec3(0.0f),
			glm::vec3(x_width, height, 0.01f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		AddChild(wall_1);

		Wall* wall_2 = new Wall(this,
			glm::vec3(x_width / 2.0f, height / 2.0f, 0.0f),
			glm::vec3(0.0f),
			glm::vec3(0.01f, height, z_width),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		AddChild(wall_2);

		Wall* wall_3 = new Wall(this,
			glm::vec3(-x_width / 2.0f, height / 2.0f, 0.0f),
			glm::vec3(0.0f),
			glm::vec3(0.01f, height, z_width),
			glm::vec3(0.0f, 0.1f, 0.1f)
		);
		AddChild(wall_3);

		Ground* roof = new Ground(this,
			glm::vec3(0.0f, height, 0.0f),
			glm::vec3(0.0f),
			glm::vec3(x_width, 1.0f, z_width),
			glm::vec3(0.5f, 0.5f, 0.5f)
		);
		AddChild(roof);

		pt_light = {
			glm::vec3(GetTransform()->position.x, height / 2.0f, GetTransform()->position.z),
			1.0f, 0.022f, 0.0019f,
			glm::vec3(0.7f, 0.7f, 0.7f),
			glm::vec3(0.7f, 0.7f, 0.7f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		};
	}

	void SetRenderParameters(Shader* p_shader)
	{
		GameObject::SetRenderParameters(p_shader);

		p_shader->SetInt("numberPointLights", 1);

		p_shader->SetVec3("pointLights[0].position", pt_light.position);
		p_shader->SetVec3("pointLights[0].ambient", pt_light.ambient);
		p_shader->SetVec3("pointLights[0].difuse", pt_light.diffuse);
		p_shader->SetVec3("pointLights[0].specular", pt_light.specular);
		p_shader->SetFloat("pointLights[0].constant", pt_light.constant);
		p_shader->SetFloat("pointLights[0].linear", pt_light.linear);
		p_shader->SetFloat("pointLights[0].quadratic", pt_light.quadratic);
	}

private:
	float x_width, z_width;
	float height;

	PointLight pt_light;
};