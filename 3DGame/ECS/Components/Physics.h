#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ecs.h"
#include "collider.h"

class Physics : public Component
{
public:
	Physics()
		: Component("physics")
	{
		direction = glm::vec3(0.0f);
		velocity_vector = glm::vec3(0.0f);
		fall_speed = 0.0f;

		running = false;
		crouched = false;
		grounded = false;

		p_game_object_collider = nullptr;
	}

	void Start()
	{
		p_game_object_collider = p_game_object->GetComponent<Collider>("collider");
	};

	void Update(float dt)
	{
		
		WalkAndRunVelocity(dt);

		p_game_object->GetTransform()->position += velocity_vector;
		//GRAVITY
		fall_speed = approach(fall_speed, MAX_FALL_SPEED, dt * GRAVITY);
		p_game_object->GetTransform()->position.y -= fall_speed * dt;

		if (p_game_object_collider)
		{
			p_game_object_collider->UpdateColliderPosition(p_game_object->GetTransform()->position);
		}
	};

	void SetDirection(float x, float y, float z)
	{
		direction = glm::vec3(x, y, z);
	}

	void SetRunning(bool r)
	{
		this->running = r;
	}

	void SetCrouched(bool c)
	{
		this->crouched = c;
	}

	void SetGrounded(bool g, float y_pos)
	{
		if (g) {
			grounded = true;
			fall_speed = 0.0f;
			p_game_object->GetTransform()->position.y = y_pos;
		}
		else
		{
			grounded = false;
		}
	}

	void Jump(float dt)
	{
		if (grounded)
		{
			fall_speed = -JUMP_SPEED;
			grounded = false;
		}
	}

	//TODO: MAKE THIS WORK
	/*void WallJump(float dt)
	{
		if (grounded) return;

		if (gameObjectCollider->GetCollisonAxis()[COLLISION_X_GREATER])
		{
			velocityVector.x = 7.5;
			fallSpeed = -JUMP_SPEED;
			grounded = false;
		}
		if (gameObjectCollider->GetCollisonAxis()[COLLISION_X_LOWER])
		{
			velocityVector.x = -7.5;
			fallSpeed = -JUMP_SPEED;
			grounded = false;
		}
		if (gameObjectCollider->GetCollisonAxis()[COLLISION_Z_GREATER])
		{
			velocityVector.z = 7.5;
			fallSpeed = -JUMP_SPEED;
			grounded = false;
		}
		if (gameObjectCollider->GetCollisonAxis()[COLLISION_Z_LOWER])
		{
			velocityVector.z = -7.5;
			fallSpeed = -JUMP_SPEED;
			grounded = false;
		}
	}*/

private:
	const float MAX_VELOCITY = 10.0f;
	const float MAX_RUNNING_VELOCITY = 20.0f;
	const float MAX_CROUCHED_VELOCITY = 5.0f;
	const float ACCELERATION_SPEED = 1000.0f;
	const float DECCELERATION_SPEED = 5000.0f;

	const float GRAVITY = 20.0f;
	const float MAX_FALL_SPEED = 10.0f; 

	const float JUMP_SPEED = 7.5f;

	glm::vec3 velocity_vector;
	glm::vec3 direction;
	float fall_speed;

	bool running;
	bool crouched;
	bool grounded;

	Collider* p_game_object_collider;

	void WalkAndRunVelocity(float dt)
	{
		//printf("%.6f\n", velocity);
		//printf("%.6f %.6f %.6f\n", gameObject->GetTransform()->position.x, gameObject->GetTransform()->position.y, gameObject->GetTransform()->position.z);
		if (glm::length(direction) > 0.0f)
		{
			glm::vec3 targetVelocity = direction * MAX_VELOCITY;
			if (crouched)
			{
				targetVelocity = direction * MAX_CROUCHED_VELOCITY;
			} 
			else if (running)
			{
				targetVelocity = direction * MAX_RUNNING_VELOCITY;
			}

			velocity_vector = approachVec3(velocity_vector, targetVelocity, ACCELERATION_SPEED * dt);
		}
		else
		{
			velocity_vector = approachVec3(velocity_vector, glm::vec3(0.0f), DECCELERATION_SPEED * dt);
		}

		velocity_vector *= dt;
	}
};