#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexAttribute
{
	GLenum type;
	unsigned int count;
	char normalised;
};

class Layout
{
private:
	unsigned int m_stride = 0;
public:

	std::vector<VertexAttribute> attributes;

	void push(GLenum type, unsigned int count, bool normalised);
	void push(GLenum type, unsigned int count);

	unsigned int sizeofGLType(GLenum type) const;

	inline unsigned int getStride() const
	{ return m_stride; }
};
