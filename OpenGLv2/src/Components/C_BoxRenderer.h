#pragma once
#include "../Rendering/Renderer.h"
#include <Eigen/Dense>

class BoxRenderer
{
protected:
	Eigen::Vector2f m_offset;
	Eigen::Vector2f m_size;
	Eigen::Vector4f m_color;

	VertexArrayObject m_vao;
	IndexBuffer m_ib;
	Shader m_shader;
public:
	BoxRenderer() = default;

	void innit(const Eigen::Vector2f& offset, const Eigen::Vector2f& size, const Eigen::Vector4f& color);

	void Render(const Eigen::Vector2f& pos);

	inline void setSize(const Eigen::Vector2f& size)
	{ m_size = size; }

	inline const Eigen::Vector2f& getSize() const
	{ return m_size; }

	inline void setOffset(const Eigen::Vector2f& offset)
	{ m_offset = offset; }

	inline const Eigen::Vector2f& getOffset() const
	{ return m_offset; }

	inline void setColor(const Eigen::Vector4f& color)
	{ m_color = color; }

	inline const Eigen::Vector4f& getColor() const
	{ return m_color; }
};