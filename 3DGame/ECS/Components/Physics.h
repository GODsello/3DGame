#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ECS.h"
#include "Collider.h"

class Physics : public Component
{
public:
	Physics()
		: Component("physics")
	{
		direction = glm::vec3(0.0f);
		velocityVector = glm::vec3(0.0f);
		velocity = 0.0f;
		fallSpeed = 0.0f;

		running = false;
		crouched = false;
		grounded = false;

		gameObjectCollider = nullptr;
	}

	void Start()
	{
		gameObjectCollider = gameObject->GetComponent<Collider>("collider");
	};

	void Update(float dt)
	{
		glm::vec3 walkVel = WalkAndRunVelocity(dt);
		velocityVector.x = walkVel.x;
		velocityVector.z = walkVel.z;

		gameObject->GetTransform()->position += velocityVector;
		//GRAVITY
		fallSpeed = approach(fallSpeed, MAX_FALL_SPEED, dt * GRAVITY);
		gameObject->GetTransform()->position.y -= fallSpeed * dt;

		if (gameObjectCollider)
		{
			gameObjectCollider->UpdateColliderPosition(gameObject->GetTransform()->position);
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

	void SetGrounded(bool g, float yPos)
	{
		if (g) {
			grounded = true;
			fallSpeed = 0.0f;
			gameObject->GetTransform()->position.y = yPos;
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
			fallSpeed = -JUMP_SPEED;
			grounded = false;
		}
	}

private:
	const float MAX_VELOCITY = 10.0f;
	const float MAX_RUNNING_VELOCITY = 15.0f;
	const float MAX_CROUCHED_VELOCITY = 5.0f;
	const float ACCELERATION_SPEED = 10.0f;
	const float DECCELERATION_SPEED = 75.0f;

	const float GRAVITY = 20.0f;
	const float MAX_FALL_SPEED = 10.0f; 

	const float JUMP_SPEED = 7.5f;

	glm::vec3 velocityVector;
	glm::vec3 direction;
	float velocity;
	float fallSpeed;

	bool running;
	bool crouched;
	bool grounded;

	Collider* gameObjectCollider;

	glm::vec3 WalkAndRunVelocity(float dt)
	{
		//printf("%.6f\n", velocity);
		//printf("%.6f %.6f %.6f\n", gameObject->GetTransform()->position.x, gameObject->GetTransform()->position.y, gameObject->GetTransform()->position.z);
		if (glm::length(direction) > 0.0f)
		{
			float targetVelocity = MAX_VELOCITY;
			if (crouched)
			{
				targetVelocity = MAX_CROUCHED_VELOCITY;
			} 
			else if (running)
			{
				targetVelocity = MAX_RUNNING_VELOCITY;
			}

			velocity = approach(velocity, targetVelocity, ACCELERATION_SPEED * dt * 1000);
		}
		else
		{
			velocity = approach(velocity, 0.0f, DECCELERATION_SPEED * dt * 1000);
		}

		return direction * velocity * dt;
	}
};