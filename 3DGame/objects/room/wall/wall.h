#pragma once

#include "../../../ecs/ecs.h"
#include "../../../ecs/components/components.h"
#include "../../../mesh/types/verticalplain.h"

class Wall : public GameObject
{
public:
	Wall(
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 color = glm::vec3(1.0f)
	) : GameObject("wall", position, rotation, scale, color)
	{
		AddMesh(VerticalPlain::GetInstance(scale.x >= scale.z));
		Collider* collW = new Collider(COLLIDER_TYPE_BOX, GetTransform()->position);
		glm::vec3 currScale = GetTransform()->scale;
		collW->SetBoxSizeParameters(
			currScale.x / 2.0f, currScale.x / 2.0f,
			currScale.y / 2.0f, currScale.y / 2.0f,
			currScale.z / 2.0f, currScale.z / 2.0f
		);
		AddComponent(collW);
	}

	Wall(GameObject* parent,
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 color = glm::vec3(1.0f)
	) : GameObject("wall", parent)
	{
		SetPosition(position);
		SetRotation(rotation);
		SetScale(scale);
		SetColor(color.r, color.g, color.b);
		glm::vec3 this_scale = GetTransform()->scale;
		AddMesh(VerticalPlain::GetInstance(this_scale.x >= this_scale.z));
		Collider* collW = new Collider(COLLIDER_TYPE_BOX, GetTransform()->position);
		collW->SetBoxSizeParameters(
			this_scale.x / 2.0f, this_scale.x / 2.0f,
			this_scale.y / 2.0f, this_scale.y / 2.0f,
			this_scale.z / 2.0f, this_scale.z / 2.0f
		);
		AddComponent(collW);
	}
};