#pragma once
#include "Layout.h"

class VertexArrayObject
{
private:
	unsigned int m_renderID;
	unsigned int m_vbRenderID;
	unsigned int m_vbSize;
public:
	VertexArrayObject();
	VertexArrayObject(const Layout& layout);
	void innit(const Layout& layout);

	~VertexArrayObject();

	void updateVertexBuffer(const void* data, unsigned int size);

	void bind() const;

	void unbind() const;
};