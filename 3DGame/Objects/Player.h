#pragma once

#include "../ecs/ecs.h"
#include "../systems/systems.h"
#include "../camera/camera.h"
#include "stats.h"

class Player : public GameObject {
public:
	Player(std::string name, Camera* p_cam, glm::vec3 position);
	void Start();
	void Update(float dt);

	void OnCollision(GameObject* p_collision);

	Stats* GetStats() { return &player_stats; }

private:
	Camera* p_camera;
	Physics* p_physics;
	Collider* p_collider;

	Stats player_stats;
};