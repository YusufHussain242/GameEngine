#pragma once

class IndexBuffer
{
private:
	unsigned int m_renderID;
	unsigned int m_count;
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned int* data, unsigned int count);
	void innit(const unsigned int* data, unsigned int count);

	~IndexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int getCount() const;
};