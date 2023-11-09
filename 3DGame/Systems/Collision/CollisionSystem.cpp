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
	return	c1.maxX > c2.minX && c1.minX < c2.maxX &&
		c1.maxY > c2.minY && c1.minY < c2.maxY &&
		c1.maxZ > c2.minZ && c1.minZ < c2.maxZ;
}

//TODO: FIX LATERAL COLLISION
bool CollisionSystem::IsYGroundedCollision(ColliderParameters object, ColliderParameters ground)
{
	return object.maxY > ground.minY && object.minY < ground.maxY;
}

bool CollisionSystem::IsXBoxesCollision(ColliderParameters object, ColliderParameters coll)
{
	return object.maxX > coll.minX && object.minX < coll.maxX;
}

bool CollisionSystem::IsZBoxesCollision(ColliderParameters object, ColliderParameters coll)
{
	return object.maxZ > coll.minZ && object.minZ < coll.maxZ;
}

unsigned int CollisionSystem::GetCollisionSide(ColliderParameters object, ColliderParameters coll)
{
	unsigned int collisionSide = COLLISION_X_GREATER;
	float currentMinDistance = 10.0f;

	float distance = abs(object.minX - coll.maxX);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_X_GREATER;
		currentMinDistance = distance;
	}

	distance = abs(object.maxX - coll.minX);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_X_LOWER;
		currentMinDistance = distance;
	}

	distance = abs(object.minY - coll.maxY);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Y_GREATER;
		currentMinDistance = distance;
	}

	distance = abs(object.maxY - coll.minY);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Y_LOWER;
		currentMinDistance = distance;
	}

	distance = abs(object.minZ - coll.maxZ);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Z_GREATER;
		currentMinDistance = distance;
	}

	distance = abs(object.maxZ - coll.minZ);
	if (distance < currentMinDistance)
	{
		collisionSide = COLLISION_Z_LOWER;
		currentMinDistance = distance;
	}

	return collisionSide;
}