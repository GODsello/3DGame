#include "CollisionSystem.h"

void CollisionSystem::CheckAllCollisions(std::vector<GameObject*>& gameObjects)
{
	for (int i = 1; i < gameObjects.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			CheckGameObjectGameObjectCollision(gameObjects[i], gameObjects[j]);
		}
	}
}

void CollisionSystem::CheckGameObjectAllCollisions(GameObject* g, std::vector<GameObject*>& gameObjects)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (g->GetName() == gameObjects[i]->GetName()) continue;

		CheckGameObjectGameObjectCollision(g, gameObjects[i]);
	}
}

void CollisionSystem::CheckGameObjectGameObjectCollision(GameObject* g1, GameObject* g2)
{
	if (g1->GetName() == g2->GetName()) return;

	Collider* g1Collider = g1->GetComponent<Collider>("collider");
	Collider* g2Collider = g2->GetComponent<Collider>("collider");

	if (!g1Collider || !g2Collider) return;

	unsigned int g1Type = g1Collider->GetType();
	unsigned int g2Type = g2Collider->GetType();

	bool collision = false;

	if (g1Type == COLLIDER_TYPE_BOX && g2Type == COLLIDER_TYPE_BOX)
	{
		collision = CheckBoxBoxCollision(g1Collider->GetParameters(), g2Collider->GetParameters());
	}

	if (collision)
	{
		g1->OnCollision(g2);
		g2->OnCollision(g1);
	}
}

bool CollisionSystem::CheckBoxBoxCollision(ColliderParameters c1, ColliderParameters c2)
{
	return	c1.max_x > c2.min_x && c1.min_x < c2.max_x &&
		c1.max_y > c2.min_y && c1.min_y < c2.max_y &&
		c1.max_z > c2.min_z && c1.min_z < c2.max_z;
}

bool CollisionSystem::IsYGroundedCollision(ColliderParameters object, ColliderParameters ground)
{
	return object.max_y > ground.min_y && object.min_y < ground.max_y;
}

bool CollisionSystem::IsXBoxesCollision(ColliderParameters object, ColliderParameters coll)
{
	return object.max_x > coll.min_x && object.min_x < coll.max_x;
}

bool CollisionSystem::IsZBoxesCollision(ColliderParameters object, ColliderParameters coll)
{
	return object.max_z > coll.min_z && object.min_z < coll.max_z;
}

unsigned int CollisionSystem::GetCollisionSide(ColliderParameters object, ColliderParameters coll)
{
	unsigned int collisionSide = COLLISION_X_GREATER;
	float currentMinDistance = 10.0f;

	float distance = abs(object.min_x - coll.max_x);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_X_GREATER;
		currentMinDistance = distance;
	}

	distance = abs(object.max_x - coll.min_x);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_X_LOWER;
		currentMinDistance = distance;
	}

	distance = abs(object.min_y - coll.max_y);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Y_GREATER;
		currentMinDistance = distance;
	}

	distance = abs(object.max_y - coll.min_y);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Y_LOWER;
		currentMinDistance = distance;
	}

	distance = abs(object.min_z - coll.max_z);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Z_GREATER;
		currentMinDistance = distance;
	}

	distance = abs(object.max_z - coll.min_z);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Z_LOWER;
		currentMinDistance = distance;
	}

	return collisionSide;
}