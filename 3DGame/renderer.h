#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "Input/KeyListener.h"
#include "Input/MouseListener.h"

static int SCR_WIDTH = 1920;
static int SCR_HEIGHT = 1080;

class Renderer
{
public:
	GLFWwindow* window;

	Renderer() 
	{
		window = nullptr;
	}

	~Renderer() { DestroyRenderer(); }

	//		Initialized glfw, glad and creates window
	//------------------------------------------------------------------------------
	bool InitRenderer(int screenWidth, int screenHeight, const char* title)
	{
		//Initialize GLFW
		if (glfwInit() == GLFW_FALSE)
		{
			printf("Failed to initialize GLFW\n");
			return false;
		}

		//Set OpenGL versions
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		//Window creation
		window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
		if (window == NULL)
		{
			printf("Failed to create window\n");
			glfwTerminate();
			return false;
		}

		//Init callbacks
		glfwSetKeyCallback(window, KeyListener::keyCallback);
		glfwSetCursorPosCallback(window, MouseListener::mousePosCallback);
		glfwSetScrollCallback(window, MouseListener::mouseScrollCallback);
		glfwSetMouseButtonCallback(window, MouseListener::mouseButtonCallback);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwMakeContextCurrent(window);

		//Load GLAD functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize glad functions\n");
			return false;
		}

		//Enable Depth test
		glEnable(GL_DEPTH_TEST);

		MouseListener::setScreenSize(SCR_WIDTH, SCR_HEIGHT);

		return true;
	}

	//		Returns if the window should be closed
	//------------------------------------------------------------------------------
	bool ShouldCloseWindow() { return glfwWindowShouldClose(window); }

	//		Swaps OpenGL buffers
	//------------------------------------------------------------------------------
	void SwapBuffers()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//		Clears window render with the color specified
	//------------------------------------------------------------------------------
	void ClearRender(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//		Destroys window and terminates glfw
	//------------------------------------------------------------------------------
	void DestroyRenderer()
	{
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
	}

};