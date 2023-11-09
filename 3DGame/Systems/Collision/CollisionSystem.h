#pragma once

#include <vector>

#include "../../ECS/ECS.h"
#include "../../ECS/Components/Components.h"

class CollisionSystem
{
public:
	static void CheckAllCollisions(std::vector<GameObject*>& gameObjects);

	static void CheckGameObjectAllCollisions(GameObject* g, std::vector<GameObject*>& gameObjects);

	static void CheckGameObjectGameObjectCollision(GameObject* g1, GameObject* g2);

	static bool CheckBoxBoxCollision(ColliderParameters c1, ColliderParameters c2);

	static bool IsYGroundedCollision(ColliderParameters object, ColliderParameters ground);

	static bool IsXBoxesCollision(ColliderParameters object, ColliderParameters coll);

	static bool IsZBoxesCollision(ColliderParameters object, ColliderParameters coll);

	static unsigned int GetCollisionSide(ColliderParameters object, ColliderParameters coll);
};