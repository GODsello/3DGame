#pragma once

#include <string>

#include "../ecs.h"
#include "physics.h"
#include "../../camera/camera.h"
#include "../../input/keylistener.h"
#include "../../input/mouselistener.h"

class Controller : public Component
{
public:

	Controller(Camera* p_cam)
		: Component("controller")
	{
		p_camera = p_cam;
		p_physics = nullptr;

		this->camera_height = CAMERA_HEIGHT;
	}

	void Start() 
	{
		p_physics = p_game_object->GetComponent<Physics>("physics");
	};

	void Update(float dt)
	{
		this->p_camera->SetPosition(this->p_game_object->GetTransform()->position
									+ glm::vec3(0.0f, camera_height, 0.0f));
		p_camera->ProcessMouseMovement(MouseListener::GetXOffset(), MouseListener::GetYOffset());
		MouseListener::ResetLastPosition();

		if (KeyListener::IsPressed(GLFW_KEY_LEFT_CONTROL))
		{
			Crouch(dt);
		}
		else
		{
			StandUp(dt);
		}

		Jump(dt);

		WalkAndRun(dt);

		//WallJump(dt);

	};

	//TODO: MAKE THIS WORK
	/*void WallJump(float dt)
	{
		if (KeyListener::isPressed(GLFW_KEY_SPACE))
		{
			physics->WallJump(dt);
		}
	}*/

	void WalkAndRun(float dt)
	{
		glm::vec3 front = glm::vec3(p_camera->front.x, 0.0f, p_camera->front.z);
		glm::vec3 right = glm::vec3(p_camera->right.x, 0.0f, p_camera->right.z);
		glm::vec3 direction = glm::vec3(0.0f);

		if (KeyListener::IsPressed(GLFW_KEY_W))
		{
			direction += front;
		}
		if (KeyListener::IsPressed(GLFW_KEY_S))
		{
			direction -= front;
		}
		if (KeyListener::IsPressed(GLFW_KEY_D))
		{
			direction += right;
		}
		if (KeyListener::IsPressed(GLFW_KEY_A))
		{
			direction -= right;
		}

		if (glm::length(direction) > 0.0f)
		{
			direction = glm::normalize(direction);
		}

		if (KeyListener::IsPressed(GLFW_KEY_LEFT_SHIFT))
		{
			p_physics->SetRunning(true);
		}
		else
		{
			p_physics->SetRunning(false);
		}

		p_physics->SetDirection(direction.x, direction.y, direction.z);
	}

	void Jump(float dt)
	{
		if (KeyListener::IsPressed(GLFW_KEY_SPACE))
		{
			p_physics->Jump(dt);
		}
	}

	void Crouch(float dt)
	{
		camera_height = approach(camera_height, CAMERA_CROUCHED_HEIGHT, crouch_velocity * dt);
		p_physics->SetCrouched(true);
	}

	void StandUp(float dt)
	{
		camera_height = approach(camera_height, CAMERA_HEIGHT, crouch_velocity * dt);
		p_physics->SetCrouched(false);
	}

private:
	Camera* p_camera;
	Physics* p_physics;

	const float CAMERA_HEIGHT = 2.0f;
	const float CAMERA_CROUCHED_HEIGHT = 0.75f;

	float camera_height;
	float crouch_velocity = 3.5f;
};