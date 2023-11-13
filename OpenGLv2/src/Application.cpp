#include "Application.h"

int main(void)
{
	Window::createWindow(1920, 1080);

	Level1 level1;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Window::window))
	{
		/* Render here */
		Renderer::clear();

		level1.step();

		/* Swap front and back buffers */
		glfwSwapBuffers(Window::window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}