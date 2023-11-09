#include "Player.h"

Player::Player(std::string name, Camera* cam)
	: GameObject(name)
{
	this->camera = cam;
	this->physics = nullptr;
}

void Player::Start()
{
	GameObject::Start();
	physics = GetComponent<Physics>("physics");
	collider = GetComponent<Collider>("collider");
}

void Player::Update(float dt)
{
	GameObject::Update(dt);
}

void Player::OnCollision(GameObject* collision)
{
	ColliderParameters playerParam = GetComponent<Collider>("collider")->GetParameters();
	Collider* collisionCollider = collision->GetComponent<Collider>("collider");

	/*if (CollisionSystem::IsYGroundedCollision(
			playerParam, 
			collisionParam)
		)
	{
		if (physics)
		{
			physics->SetGrounded(true, collision->GetComponent<Collider>("collider")->GetParameters().maxY);
		}
	}
	else
	{
		physics->SetGrounded(false, 0.0f);
	}*/
	
	unsigned int collisionSide = CollisionSystem::GetCollisionSide(playerParam, collisionCollider->GetParameters());

	if (physics)
	{
		collider->SetCollisionAxis(collisionSide, true);
		switch (collisionSide)
		{
			case COLLISION_Y_GREATER:
			{
				physics->SetGrounded(true, collisionCollider->GetParameters().maxY);
				break;
			}
			case COLLISION_X_LOWER:
			{
				GetTransform()->position.x = collisionCollider->GetParameters().minX - (playerParam.maxX - GetTransform()->position.x);
				break;
			}
			case COLLISION_X_GREATER:
			{
				GetTransform()->position.x = collisionCollider->GetParameters().maxX + (GetTransform()->position.x - playerParam.minX);
				break;
			}
			case COLLISION_Z_LOWER:
			{
				GetTransform()->position.z = collisionCollider->GetParameters().minZ - (playerParam.maxZ - GetTransform()->position.z);
				break;
			}
			case COLLISION_Z_GREATER:
			{
				GetTransform()->position.z = collisionCollider->GetParameters().maxZ + (GetTransform()->position.z - playerParam.minZ);
				break;
			}
			default:
				break;
		}

	}
}