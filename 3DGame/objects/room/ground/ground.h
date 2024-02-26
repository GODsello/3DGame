#pragma once

#include "../../../ecs/ecs.h"
#include "../../../ecs/components/components.h"
#include "../../../mesh/types/horizontalplain.h"

class Ground : public GameObject
{
public:
	Ground(
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 color = glm::vec3(1.0f)
	) : GameObject("ground", position, rotation, scale, color)
	{
		AddMesh(HorizontalPlain::GetInstance());
		Collider* collG = new Collider(COLLIDER_TYPE_BOX, GetTransform()->position);
		glm::vec3 currScale = GetTransform()->scale;
		collG->SetBoxSizeParameters(
			currScale.x / 2.0f, currScale.x / 2.0f, 
			0.01f, 0.00f, 
			currScale.z / 2.0f, currScale.z / 2.0f
		);
		AddComponent(collG);
	}

	Ground(GameObject* parent,
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 color = glm::vec3(1.0f)
	) : GameObject("ground", parent)
	{
		SetPosition(position);
		SetRotation(rotation);
		SetScale(scale);
		SetColor(color.r, color.g, color.b);
		AddMesh(HorizontalPlain::GetInstance());
		Collider* collG = new Collider(COLLIDER_TYPE_BOX, GetTransform()->position);
		glm::vec3 this_scale = GetTransform()->scale;
		collG->SetBoxSizeParameters(this_scale.x / 2.0f, this_scale.x / 2.0f, 0.01f, 0.00f, this_scale.z / 2.0f, this_scale.z / 2.0f);
		AddComponent(collG);
	}
};