#pragma once
#include <GLFW/glfw3.h>

class KeyListener
{
public:
	static KeyListener* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new KeyListener();
		}

		return instance;
	}

	static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			getInstance()->keyPressed[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			getInstance()->keyPressed[key] = false;
		}
	}

	static bool isPressed(int keyCode)
	{
		return getInstance()->keyPressed[keyCode];
	}

	KeyListener(const KeyListener& keyL) = delete;

private:
	static KeyListener* instance;

	bool keyPressed[GLFW_KEY_LAST];

	KeyListener(){
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			keyPressed[i] = false;
		}
	}
};