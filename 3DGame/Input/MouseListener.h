#pragma once
#include <GLFW/glfw3.h>

#include <stdio.h>

class MouseListener
{
public:

	static MouseListener* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new MouseListener();
		}

		return instance;
	}

	static void mousePosCallback(GLFWwindow* window, double x, double y)
	{
		getInstance()->xPos = static_cast<float>(x);
		getInstance()->yPos = static_cast<float>(y);		
	}

	static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		getInstance()->scrollX = static_cast<float>(xOffset);
		getInstance()->scrollY = static_cast<float>(yOffset);
	}

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS && button < sizeof(getInstance()->mouseButtonPressed) / sizeof(bool))
		{
			getInstance()->mouseButtonPressed[button] = true;
		}
		else if (action == GLFW_RELEASE && button < sizeof(getInstance()->mouseButtonPressed) / sizeof(bool))
		{
			getInstance()->mouseButtonPressed[button] = false;
		}
	}

	static void ResetLastPosition()
	{
		getInstance()->lastX = getInstance()->xPos;
		getInstance()->lastY = getInstance()->yPos;
	}

	static void endFrame()
	{
		getInstance()->scrollX = 0;
		getInstance()->scrollY = 0;
		getInstance()->lastX = getInstance()->xPos;
		getInstance()->lastY = getInstance()->yPos;
	}

	static float getX() { return getInstance()->xPos; }
	static float getY() { return getInstance()->yPos; }

	static float getLastX() { return getInstance()->lastX; }
	static float getLastY() { return getInstance()->lastY; }

	static float getScrollX() { return getInstance()->scrollX; }

	static float getScrollY() { return getInstance()->scrollY; }

	static float getXOffset() { return getInstance()->xPos - getInstance()->lastX; }

	static float getYOffset() { return getInstance()->lastY - getInstance()->yPos; }

	static bool getMouseButtonDown(int button)
	{
		if (button < sizeof(getInstance()->mouseButtonPressed) / sizeof(bool))
		{
			return getInstance()->mouseButtonPressed[button];
		}
		
		return false;
	}

	static void setScreenSize(unsigned int screenWidth, unsigned int screenHeight)
	{
		getInstance()->xPos = screenWidth / 2.0f;
		getInstance()->yPos = screenHeight / 2.0f;
		getInstance()->lastX = screenWidth / 2.0f;
		getInstance()->lastY = screenHeight / 2.0f;
	}

private:
	static MouseListener* instance;
	float scrollX, scrollY;
	float xPos, yPos;
	float lastX, lastY;

	bool mouseButtonPressed[3];

	MouseListener()
	{
		scrollX = 0;
		scrollY = 0;
		xPos = 0;
		yPos = 0;
		lastX = 0;
		lastY = 0;

		for (int i = 0; i < sizeof(getInstance()->mouseButtonPressed) / sizeof(bool); i++)
		{
			mouseButtonPressed[i] = false;
		}
	}
};