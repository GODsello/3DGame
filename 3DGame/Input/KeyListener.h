#pragma once
#include <GLFW/glfw3.h>

class KeyListener
{
public:

	static KeyListener* GetInstance()
	{
		if (p_instance == nullptr)
		{
			p_instance = new KeyListener();
		}

		return p_instance;
	}

	static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			GetInstance()->key_pressed[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			GetInstance()->key_pressed[key] = false;
		}
	}

	static bool IsPressed(int key_code)
	{
		return GetInstance()->key_pressed[key_code];
	}

	KeyListener(const KeyListener& keyL) = delete;

private:
	static KeyListener* p_instance;

	bool key_pressed[GLFW_KEY_LAST];

	KeyListener(){
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			key_pressed[i] = false;
		}
	}
};