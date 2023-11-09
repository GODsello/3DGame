#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ECS.h"

enum ColliderTypes
{
	COLLIDER_TYPE_BOX,
	
	COLLIDER_TYPE_COUNT
};

enum NearestCollision
{
	COLLISION_X_GREATER,
	COLLISION_X_LOWER,
	COLLISION_Y_GREATER,
	COLLISION_Y_LOWER,
	COLLISION_Z_GREATER,
	COLLISION_Z_LOWER,
	COLLISION_AXIS_COUNT
};

struct ColliderParameters
{
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;
};

class Collider : public Component
{
public:
	Collider(unsigned int type)
		: Component("collider")
	{
		this->type = type;
		this->parameters = {};
		this->position = glm::vec3(0.0f);
		ResetCollisionAxis();
	}

	Collider(unsigned int type, glm::vec3 position)
		: Collider(type)
	{
		this->position = position;
	}

	void SetBoxParameters(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
	{
		parameters.minX = minX;
		parameters.maxX = maxX;
		parameters.minY = minY;
		parameters.maxY = maxY;
		parameters.minZ = minZ;
		parameters.maxZ = maxZ;
	}

	void UpdateColliderPosition(glm::vec3 newPos)
	{
		glm::vec3 offsets = newPos - position;

		if (type == COLLIDER_TYPE_BOX)
		{
			parameters.minX += offsets.x;
			parameters.maxX += offsets.x;
			parameters.minY += offsets.y;
			parameters.maxY += offsets.y;
			parameters.minZ += offsets.z;
			parameters.maxZ += offsets.z;
		}

		position = newPos;
	}

	void ResetCollisionAxis()
	{
		for (int i = 0; i < COLLISION_AXIS_COUNT; i++)
		{
			collisionAxis[i] = false;
		}
	}

	void SetCollisionAxis(unsigned int axis, bool value)
	{
		collisionAxis[axis] = value;
	}

	unsigned int GetType() { return type; }
	
	ColliderParameters& GetParameters() { return parameters; }

	void Start(){}
	void Update(float dt)
	{
		ResetCollisionAxis();
	}

private:
	unsigned int type;
	ColliderParameters parameters;
	bool collisionAxis[COLLISION_AXIS_COUNT];

	glm::vec3 position;
};