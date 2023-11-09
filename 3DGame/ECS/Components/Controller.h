#pragma once

#include <string>

#include "../ECS.h"
#include "Physics.h"
#include "../../Camera/camera.h"
#include "../../Input/KeyListener.h"
#include "../../Input/MouseListener.h"

class Controller : public Component
{
public:

	Controller(Camera* cam)
		: Component("controller")
	{
		camera = cam;
		physics = nullptr;
		collider = nullptr;

		this->cameraHeight = CAMERA_HEIGHT;
	}

	void Start() 
	{
		physics = gameObject->GetComponent<Physics>("physics");
		collider = gameObject->GetComponent<Collider>("collider");
	};

	void Update(float dt)
	{
		this->camera->SetPosition(this->gameObject->GetTransform()->position
									+ glm::vec3(0.0f, cameraHeight, 0.0f));
		camera->ProcessMouseMovement(MouseListener::getXOffset(), MouseListener::getYOffset());
		MouseListener::ResetLastPosition();

		if (KeyListener::isPressed(GLFW_KEY_LEFT_CONTROL))
		{
			Crouch(dt);
		}
		else
		{
			StandUp(dt);
		}

		Jump(dt);

		WalkAndRun(dt);
	};

	void WalkAndRun(float dt)
	{
		glm::vec3 front = glm::vec3(camera->Front.x, 0.0f, camera->Front.z);
		glm::vec3 right = glm::vec3(camera->Right.x, 0.0f, camera->Right.z);
		glm::vec3 direction = glm::vec3(0.0f);

		if (KeyListener::isPressed(GLFW_KEY_W))
		{
			direction += front;
		}
		if (KeyListener::isPressed(GLFW_KEY_S))
		{
			direction -= front;
		}
		if (KeyListener::isPressed(GLFW_KEY_D))
		{
			direction += right;
		}
		if (KeyListener::isPressed(GLFW_KEY_A))
		{
			direction -= right;
		}

		if (glm::length(direction) > 0.0f)
		{
			direction = glm::normalize(direction);
		}

		if (KeyListener::isPressed(GLFW_KEY_LEFT_SHIFT))
		{
			physics->SetRunning(true);
		}
		else
		{
			physics->SetRunning(false);
		}

		physics->SetDirection(direction.x, direction.y, direction.z);
	}

	void Jump(float dt)
	{
		if (KeyListener::isPressed(GLFW_KEY_SPACE))
		{
			physics->Jump(dt);
		}
	}

	void Crouch(float dt)
	{
		cameraHeight = approach(cameraHeight, CAMERA_CROUCHED_HEIGHT, crouchVelocity * dt);
		physics->SetCrouched(true);
	}

	void StandUp(float dt)
	{
		cameraHeight = approach(cameraHeight, CAMERA_HEIGHT, crouchVelocity * dt);
		physics->SetCrouched(false);
	}

private:
	Camera* camera;
	Physics* physics;
	Collider* collider;

	const float CAMERA_HEIGHT = 1.5f;
	const float CAMERA_CROUCHED_HEIGHT = 0.5f;
	float cameraHeight;
	float crouchVelocity = 3.5f;
};