#include "renderer.h"
#include <iostream>

void GLClearError() { while (glGetError()); }
bool GLCheckError(const char* function, const char* filePath, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[Open GL Error]: " << "(" << error << ") " << function << " " << filePath << ": " << line << "\n";
		return false;
	}
	return true;
}

void Renderer::draw(const VertexArrayObject& vao, const IndexBuffer& ib, const Shader& shader)
{
	vao.bind();
	ib.bind();
	shader.bind();
	GLCALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
