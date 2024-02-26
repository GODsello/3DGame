#pragma once

#include "scene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();

	static void SetActiveScene(Scene* new_scene);

	static Scene* GetActiveScene() { return p_active_scene; }

private:
	static SceneManager* p_instance;
	static Scene* p_active_scene;

	SceneManager();
};