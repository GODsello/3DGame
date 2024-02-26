#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "scene/scenemanager.h"
#include "scene/defaultscene.h"

#include "systems/systems.h"

constexpr int UPDATES_PER_SECOND = 144;
constexpr float UPDATE_DELAY = 1.0 / UPDATES_PER_SECOND;

static Renderer* renderer;
static Scene* currentScene;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float renderTime = 0.0f;

int main()
{
	renderer = new Renderer();
	currentScene = new DefaultScene(0, renderer);

	if (!renderer->InitRenderer(Renderer::SCR_WIDTH, Renderer::SCR_HEIGHT, "3DGame"))
	{
		return -1;
	}

	currentScene->LoadScene();

	SceneManager::SetActiveScene(currentScene);

	currentScene->StartScene();

	while (!renderer->ShouldCloseWindow())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime += currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (deltaTime > UPDATE_DELAY)
		{
			CollisionSystem::CheckAllCollisions(*currentScene->GetSceneGameObjects());

			currentScene->ProcessInput();


			currentScene->UpdateScene(deltaTime);

			currentScene->ClearGameObjects();

			renderer->ClearRender(0.0f, 0.0f, 0.0f);

			currentScene->RenderScene();
			renderTime -= UPDATE_DELAY;

			renderer->SwapBuffers();

			deltaTime = 0.0f;
		}
	}


	delete currentScene;
	delete renderer;
	
	return 0;
}