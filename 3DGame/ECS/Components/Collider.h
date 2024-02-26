#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ecs.h"

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
	glm::vec3 position;

	float min_x, max_x;
	float min_y, max_y;
	float min_z, max_z;
};

class Collider : public Component
{
public:
	Collider(unsigned int type)
		: Component("collider")
	{
		this->type = type;
		this->parameters = {};
		this->parameters.position = glm::vec3(0.0f);
		ResetCollisionAxis();
	}

	Collider(unsigned int type, glm::vec3 position)
		: Collider(type)
	{
		this->parameters.position = position;
	}

	void SetBoxSizeParameters(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z)
	{
		parameters.min_x = parameters.position.x - min_x;
		parameters.max_x = parameters.position.x + max_x;
		parameters.min_y = parameters.position.y - min_y;
		parameters.max_y = parameters.position.y + max_y;
		parameters.min_z = parameters.position.z - min_z;
		parameters.max_z = parameters.position.z + max_z;
	}

	void UpdateColliderPosition(glm::vec3 new_pos)
	{
		glm::vec3 offsets = new_pos - parameters.position;

		if (type == COLLIDER_TYPE_BOX)
		{
			parameters.min_x += offsets.x;
			parameters.max_x += offsets.x;
			parameters.min_y += offsets.y;
			parameters.max_y += offsets.y;
			parameters.min_z += offsets.z;
			parameters.max_z += offsets.z;
		}

		parameters.position = new_pos;
	}

	void ResetCollisionAxis()
	{
		for (int i = 0; i < COLLISION_AXIS_COUNT; i++)
		{
			collision_axis[i] = false;
		}
	}

	void SetCollisionAxis(unsigned int axis, bool value)
	{
		collision_axis[axis] = value;
	}

	unsigned int GetType() { return type; }
	
	ColliderParameters& GetParameters() { return parameters; }

	bool* GetCollisonAxis() { return collision_axis; }

	void Start(){}
	void Update(float dt)
	{
		ResetCollisionAxis();
	}

private:
	unsigned int type;
	ColliderParameters parameters;
	bool collision_axis[COLLISION_AXIS_COUNT];
};