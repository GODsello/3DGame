#include "player.h"

Player::Player(std::string name, Camera* p_cam, glm::vec3 position = glm::vec3(0.0f))
	: GameObject(name)
{
	this->p_camera = p_cam;
	this->p_physics = nullptr;
	this->p_collider = nullptr;
	GetTransform()->position = position;
	Controller* c = new Controller(p_cam);
	Physics* ph = new Physics();
	Collider* coll = new Collider(COLLIDER_TYPE_BOX, position);
	coll->SetBoxSizeParameters(0.5f, 0.5f, 0.0f, 1.75f, 0.5f, 0.5f);
	AddComponent(coll);
	AddComponent(c);
	AddComponent(ph);
}

void Player::Start()
{
	GameObject::Start();
	p_physics = GetComponent<Physics>("physics");
	p_collider = GetComponent<Collider>("collider");
}

void Player::Update(float dt)
{
	GameObject::Update(dt);
}

void Player::OnCollision(GameObject* p_collision)
{
	ColliderParameters player_param = GetComponent<Collider>("collider")->GetParameters();
	Collider* p_collision_collider = p_collision->GetComponent<Collider>("collider");
	
	unsigned int collision_side = CollisionSystem::GetCollisionSide(player_param, p_collision_collider->GetParameters());

	if (p_physics)
	{
		p_collider->SetCollisionAxis(collision_side, true);
		switch (collision_side)
		{
			case COLLISION_Y_GREATER:
			{
				p_physics->SetGrounded(true, p_collision_collider->GetParameters().max_y);
				break;
			}
			case COLLISION_X_LOWER:
			{
				GetTransform()->position.x = p_collision_collider->GetParameters().min_x - (player_param.max_x - GetTransform()->position.x);
				break;
			}
			case COLLISION_X_GREATER:
			{
				GetTransform()->position.x = p_collision_collider->GetParameters().max_x + (GetTransform()->position.x - player_param.min_x);
				break;
			}
			case COLLISION_Z_LOWER:
			{
				GetTransform()->position.z = p_collision_collider->GetParameters().min_z - (player_param.max_z - GetTransform()->position.z);
				break;
			}
			case COLLISION_Z_GREATER:
			{
				GetTransform()->position.z = p_collision_collider->GetParameters().max_z + (GetTransform()->position.z - player_param.min_z);
				break;
			}
			default:
				break;
		}

	}
}