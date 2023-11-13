#include "C_Input.h"
#include "GLFW/glfw3.h"
#include "../Engine/WindowManager.h"

bool Input::isPressed(int key)
{
	if (glfwGetKey(Window::window, key) == GLFW_PRESS)
		return true;
	return false;
}