#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	GLCALL(glGenBuffers(1, &m_renderID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

	m_count = count;
}

void IndexBuffer::innit(const unsigned int* data, unsigned int count)
{
	GLCALL(glGenBuffers(1, &m_renderID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

	m_count = count;
}

IndexBuffer::~IndexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_renderID));
}

void IndexBuffer::bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderID));
}

void IndexBuffer::unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::getCount() const { return m_count; }
