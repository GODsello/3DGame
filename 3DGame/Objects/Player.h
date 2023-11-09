#pragma once

#include "../ECS/ECS.h"
#include "../Systems/Systems.h"
#include "../Camera/camera.h"

class Player : public GameObject {
public:
	Player(std::string name, Camera* cam);
	void Start();
	void Update(float dt);

	void OnCollision(GameObject* collision);

private:
	Camera* camera;
	Physics* physics;
	Collider* collider;
};