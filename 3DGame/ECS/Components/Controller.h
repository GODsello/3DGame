#pragma once

#include <string>

#include "../ECS.h"
#include "Physics.h"
#include "../../Camera/camera.h"
#include "../../Input/KeyListener.h"

class Controller : public Component
{
public:

	Controller(Camera* cam)
		: Component("controller")
	{
		camera = cam;
		physics = nullptr;

		this->cameraHeight = CAMERA_HEIGHT;
	}

	void Start() 
	{
		physics = gameObject->GetComponent<Physics>("physics");
	};

	void Update(float dt)
	{
		this->camera->SetPosition(this->gameObject->GetTransform()->position
									+ glm::vec3(0.0f, cameraHeight, 0.0f));
		camera->ProcessMouseMovement(MouseListener::getXOffset(), MouseListener::getYOffset());
		MouseListener::ResetLastPosition();

		glm::vec3 front = glm::vec3(camera->Front.x, 0.0f, camera->Front.z);
		glm::vec3 right = glm::vec3(camera->Right.x, 0.0f, camera->Right.z);
		glm::vec3 direction = glm::vec3(0.0f);

		if (KeyListener::isPressed(GLFW_KEY_LEFT_CONTROL))
		{
			Crouch();
		}
		else
		{
			StandUp();
		}
		if (KeyListener::isPressed(GLFW_KEY_W))
		{
			//gameObject->GetTransform()->position += front * dt * 1000.0f * 5.0f;
			direction += front;
		}
		if (KeyListener::isPressed(GLFW_KEY_S))
		{
			//gameObject->GetTransform()->position -= front * dt * 1000.0f * 5.0f;
			direction -= front;
		}
		if (KeyListener::isPressed(GLFW_KEY_D))
		{
			//gameObject->GetTransform()->position += right * dt * 1000.0f * 5.0f;
			direction += right;
		}
		if (KeyListener::isPressed(GLFW_KEY_A))
		{
			//gameObject->GetTransform()->position -= right * dt * 1000.0f * 5.0f;
			direction -= right;
		}

		if (glm::length(direction) > 0.0f)
		{
			direction = glm::normalize(direction);
		}

		if (KeyListener::isPressed(GLFW_KEY_LEFT_SHIFT))
		{
			direction *= 2.0f;
		}

		physics->SetDirection(direction.x, direction.y, direction.z);
	};

	void Crouch()
	{
		cameraHeight = CAMERA_CROUCHED_HEIGHT;
	}

	void StandUp()
	{
		cameraHeight = CAMERA_HEIGHT;
	}

private:
	Camera* camera;
	Physics* physics;	

	const float CAMERA_HEIGHT = 1.5f;
	const float CAMERA_CROUCHED_HEIGHT = 0.5f;
	float cameraHeight;
};