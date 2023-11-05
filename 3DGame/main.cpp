#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "utils/utils.h"
#include "Scene/DefaultScene.h"

static Renderer* renderer;
static Scene* currentScene;

int main()
{
	renderer = new Renderer();
	currentScene = new DefaultScene(0, renderer);

	if (!renderer->InitRenderer(SCR_WIDTH, SCR_HEIGHT, "3DGame"))
	{
		return -1;
	}

	currentScene->LoadScene();

	while (!renderer->ShouldCloseWindow())
	{
		currentScene->ProcessInput();

		renderer->ClearRender(0.0f, 0.0f, 0.0f);

		currentScene->RenderScene();

		renderer->SwapBuffers();
	}

	currentScene->DownloadScene();
	renderer->DestroyRenderer();

	return 0;
}