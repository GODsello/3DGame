#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ECS.h"

class Physics : public Component
{
public:
	Physics()
		: Component("physics")
	{
		direction = glm::vec3(0.0f);
	}

	void Start()
	{

	};

	void Update(float dt)
	{
		gameObject->GetTransform()->position += direction * dt * 1000.0f * 5.0f;
	};

	void SetDirection(float x, float y, float z)
	{
		direction = glm::vec3(x, y, z);
	}

private:
	glm::vec3 direction;
};