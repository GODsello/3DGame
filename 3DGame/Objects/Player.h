#pragma once

#include "../ECS/ECS.h"
#include "../Camera/camera.h"

class Player : public GameObject {
public:
	Player(std::string name, Camera* cam);
	void Update(float dt);

private:
	Camera* camera;
};