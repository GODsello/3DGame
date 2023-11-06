#include "Player.h"

Player::Player(std::string name, Camera* cam)
	: GameObject(name)
{
	this->camera = cam;
}

void Player::Update(float dt)
{
	GameObject::Update(dt);
}