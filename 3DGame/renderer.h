#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "Input/KeyListener.h"
#include "Input/MouseListener.h"

class Renderer
{
public:
	GLFWwindow* p_window;
	static const int SCR_WIDTH = 1920;
	static const int SCR_HEIGHT = 1080;

	Renderer() 
	{
		p_window = nullptr;
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
		p_window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
		if (p_window == NULL)
		{
			printf("Failed to create window\n");
			glfwTerminate();
			return false;
		}

		//Init callbacks
		glfwSetKeyCallback(p_window, KeyListener::KeyCallback);
		glfwSetCursorPosCallback(p_window, MouseListener::MousePosCallback);
		glfwSetScrollCallback(p_window, MouseListener::MouseScrollCallback);
		glfwSetMouseButtonCallback(p_window, MouseListener::MouseButtonCallback);
		//glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwMakeContextCurrent(p_window);

		//Load GLAD functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize glad functions\n");
			return false;
		}

		//Enable Depth test
		glEnable(GL_DEPTH_TEST);

		MouseListener::SetScreenSize(SCR_WIDTH, SCR_HEIGHT);

		return true;
	}

	//		Returns if the window should be closed
	//------------------------------------------------------------------------------
	bool ShouldCloseWindow() { return glfwWindowShouldClose(p_window); }

	//		Swaps OpenGL buffers
	//------------------------------------------------------------------------------
	void SwapBuffers()
	{
		glfwSwapBuffers(p_window);
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
		glfwDestroyWindow(p_window);
		p_window = nullptr;
		glfwTerminate();

		delete MouseListener::GetInstance();
		delete KeyListener::GetInstance();
	}

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
};