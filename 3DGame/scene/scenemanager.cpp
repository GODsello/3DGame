#include "scenemanager.h"

Scene* SceneManager::p_active_scene = nullptr;
SceneManager* SceneManager::p_instance = nullptr;

SceneManager::SceneManager()
{
	this->p_active_scene = nullptr;
}

SceneManager* SceneManager::GetInstance()
{
	if (p_instance == nullptr)
	{
		p_instance = new SceneManager();
	}

	return p_instance;
}

void SceneManager::SetActiveScene(Scene* new_scene)
{
	GetInstance()->p_active_scene = new_scene;
}