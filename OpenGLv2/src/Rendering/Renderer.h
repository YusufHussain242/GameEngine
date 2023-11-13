#pragma once
#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "IndexBuffer.h"
#include "Shader.h"

#ifdef _DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearError(); x; ASSERT(GLCheckError(#x, __FILE__, __LINE__))
#else
#define GLCALL(x) x
#endif

void GLClearError();
bool GLCheckError(const char* function, const char* filePath, int line);

class Renderer
{
public:
	static void draw(const VertexArrayObject& vao, const IndexBuffer& ib, const Shader& shader);
	inline static void clear()
	{ GLCALL(glClear(GL_COLOR_BUFFER_BIT)); }
};