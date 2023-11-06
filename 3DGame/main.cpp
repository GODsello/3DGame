#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "utils/utils.h"
#include "Scene/DefaultScene.h"

static Renderer* renderer;
static Scene* currentScene;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	renderer = new Renderer();
	currentScene = new DefaultScene(0, renderer);

	if (!renderer->InitRenderer(SCR_WIDTH, SCR_HEIGHT, "3DGame"))
	{
		return -1;
	}

	currentScene->LoadScene();

	currentScene->StartScene();

	while (!renderer->ShouldCloseWindow())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		currentScene->ProcessInput();

		currentScene->UpdateScene(deltaTime / 1000.0f);

		renderer->ClearRender(0.0f, 0.0f, 0.0f);

		currentScene->RenderScene();

		renderer->SwapBuffers();
	}

	currentScene->DownloadScene();
	renderer->DestroyRenderer();

	return 0;
}