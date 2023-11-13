#include "Layout.h"
#include <iostream>
#include "Renderer.h"

void Layout::push(GLenum type, unsigned int count, bool normalised)
{
	attributes.push_back({ type, count, (normalised ? GL_TRUE : GL_FALSE) });
	m_stride += count * sizeofGLType(type);
}

void Layout::push(GLenum type, unsigned int count)
{
	attributes.push_back({ type, count, GL_FALSE });
	m_stride += count * sizeofGLType(type);
}

unsigned int Layout::sizeofGLType(GLenum type) const
{
	switch (type)
	{
	case GL_FLOAT:			return sizeof(float);
	case GL_DOUBLE:			return sizeof(double);
	case GL_INT:			return sizeof(int);
	case GL_UNSIGNED_INT:	return sizeof(unsigned int);
	case GL_SHORT:			return sizeof(short);
	case GL_UNSIGNED_SHORT: return sizeof(unsigned short);
	case GL_BYTE:			return sizeof(char);
	case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
	default:
		std::cout << "Error: Type not supported\n";
		ASSERT(false);
	}
}
