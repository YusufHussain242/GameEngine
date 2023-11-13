#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
	static GLFWwindow* window;

	static int createWindow(unsigned int x, unsigned int y);
};