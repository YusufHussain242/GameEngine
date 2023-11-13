#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "Renderer.h"

VertexArrayObject::VertexArrayObject() {}

VertexArrayObject::VertexArrayObject(const Layout& layout)
{
	GLCALL(glGenVertexArrays(1, &m_renderID));
	GLCALL(glBindVertexArray(m_renderID));

	GLCALL(glGenBuffers(1, &m_vbRenderID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderID));

	unsigned int offset = 0;
	for (int i = 0; i < layout.attributes.size(); i++)
	{
		VertexAttribute attribute = layout.attributes[i];
		GLCALL(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalised, layout.getStride(), (const void*)offset));
		GLCALL(glEnableVertexAttribArray(i));
		offset += attribute.count * layout.sizeofGLType(attribute.type);
	}
}

void VertexArrayObject::innit(const Layout& layout)
{
	GLCALL(glGenVertexArrays(1, &m_renderID));
	GLCALL(glBindVertexArray(m_renderID));

	GLCALL(glGenBuffers(1, &m_vbRenderID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderID));

	unsigned int offset = 0;
	for (int i = 0; i < layout.attributes.size(); i++)
	{
		VertexAttribute attribute = layout.attributes[i];
		GLCALL(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalised, layout.getStride(), (const void*)offset));
		GLCALL(glEnableVertexAttribArray(i));
		offset += attribute.count * layout.sizeofGLType(attribute.type);
	}
}



VertexArrayObject::~VertexArrayObject()
{
	GLCALL(glDeleteVertexArrays(1, &m_renderID));
}

void VertexArrayObject::updateVertexBuffer(const void * data, unsigned int size)
{
	bind();
	if (m_vbSize == size)
	{
		GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}
	else
	{
		m_vbSize = size;
		GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}
}

void VertexArrayObject::bind() const 
{
	GLCALL(glBindVertexArray(m_renderID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderID));
}

void VertexArrayObject::unbind() const 
{ 
	GLCALL(glBindVertexArray(0));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}