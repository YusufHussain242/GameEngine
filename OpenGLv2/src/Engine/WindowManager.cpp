#include <GL/glew.h>
#include "WindowManager.h"
#include <iostream>

GLFWwindow* Window::window;

int Window::createWindow(unsigned int x, unsigned int y)
{
	/* Initialize the library */
	if (!glfwInit())
	{
		return -1;
		std::cout << "Error, cannot innitialise GLFW\n";
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(x, y, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Error, cannot create window\n";
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error, cannot innitialise GLEW\n";
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << "\n";
}
