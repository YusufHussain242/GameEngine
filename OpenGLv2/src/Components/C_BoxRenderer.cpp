#include "C_BoxRenderer.h"

void BoxRenderer::innit(const Eigen::Vector2f& offset, const Eigen::Vector2f& size, const Eigen::Vector4f& color)
{
	m_offset = offset;
	m_size = size;
	m_color = color;

	unsigned int indecies[] = {
		0, 1, 2,
		2, 0, 3
	};

	Layout layout;
	layout.push(GL_FLOAT, 2);

	m_vao.innit(layout);
	m_ib.innit(indecies, 6);
	m_shader.innit("res/shaders/Vertex.shader", "res/shaders/Fragment.shader");
}

void BoxRenderer::Render(const Eigen::Vector2f& pos)
{
	float positions[] = {
	(pos[0] + m_offset[0] - m_size[0] / 2), (pos[1] + m_offset[1] - m_size[1] / 2), //0
	(pos[0] + m_offset[0] + m_size[0] / 2), (pos[1] + m_offset[1] - m_size[1] / 2), //1
	(pos[0] + m_offset[0] + m_size[0] / 2), (pos[1] + m_offset[1] + m_size[1] / 2), //2
	(pos[0] + m_offset[0] - m_size[0] / 2), (pos[1] + m_offset[1] + m_size[1] / 2)  //3
	};

	m_vao.updateVertexBuffer(positions, 8 * sizeof(float));
	m_shader.setUniform4f("u_color", m_color);
	Renderer::draw(m_vao, m_ib, m_shader);
}
