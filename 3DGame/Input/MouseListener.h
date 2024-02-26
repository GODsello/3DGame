#pragma once
#include <GLFW/glfw3.h>

#include <stdio.h>

class MouseListener
{
public:

	static MouseListener* GetInstance()
	{
		if (p_instance == nullptr)
		{
			p_instance = new MouseListener();
		}

		return p_instance;
	}

	static void MousePosCallback(GLFWwindow* window, double x, double y)
	{
		GetInstance()->x_pos = static_cast<float>(x);
		GetInstance()->y_pos = static_cast<float>(y);		
	}

	static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		GetInstance()->scroll_x = static_cast<float>(xOffset);
		GetInstance()->scroll_y = static_cast<float>(yOffset);
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS && button < sizeof(GetInstance()->mouse_button_pressed) / sizeof(bool))
		{
			GetInstance()->mouse_button_pressed[button] = true;
		}
		else if (action == GLFW_RELEASE && button < sizeof(GetInstance()->mouse_button_pressed) / sizeof(bool))
		{
			GetInstance()->mouse_button_pressed[button] = false;
		}
	}

	static void ResetLastPosition()
	{
		GetInstance()->last_x = GetInstance()->x_pos;
		GetInstance()->last_y = GetInstance()->y_pos;
	}

	static void EndFrame()
	{
		GetInstance()->scroll_x = 0;
		GetInstance()->scroll_y = 0;
		GetInstance()->last_x = GetInstance()->x_pos;
		GetInstance()->last_y = GetInstance()->y_pos;
	}

	static float GetX() { return GetInstance()->x_pos; }
	static float GetY() { return GetInstance()->y_pos; }

	static float GetLastX() { return GetInstance()->last_x; }
	static float GetLastY() { return GetInstance()->last_y; }

	static float GetScrollX() { return GetInstance()->scroll_x; }

	static float GetScrollY() { return GetInstance()->scroll_y; }

	static float GetXOffset() { return GetInstance()->x_pos - GetInstance()->last_x; }

	static float GetYOffset() { return GetInstance()->last_y - GetInstance()->y_pos; }

	static bool GetMouseButtonDown(int button)
	{
		if (button < sizeof(GetInstance()->mouse_button_pressed) / sizeof(bool))
		{
			return GetInstance()->mouse_button_pressed[button];
		}
		
		return false;
	}

	static void SetScreenSize(unsigned int screenWidth, unsigned int screenHeight)
	{
		GetInstance()->x_pos = screenWidth / 2.0f;
		GetInstance()->y_pos = screenHeight / 2.0f;
		GetInstance()->last_x = screenWidth / 2.0f;
		GetInstance()->last_y = screenHeight / 2.0f;
	}

private:
	static MouseListener* p_instance;
	float scroll_x, scroll_y;
	float x_pos, y_pos;
	float last_x, last_y;

	bool mouse_button_pressed[3];

	MouseListener()
	{
		scroll_x = 0;
		scroll_y = 0;
		x_pos = 0;
		y_pos = 0;
		last_x = 0;
		last_y = 0;

		for (int i = 0; i < sizeof(GetInstance()->mouse_button_pressed) / sizeof(bool); i++)
		{
			mouse_button_pressed[i] = false;
		}
	}
};