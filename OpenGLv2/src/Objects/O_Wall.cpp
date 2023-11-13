#include "O_Wall.h"

Wall::Wall(Scene* scene, const Eigen::Vector2f& position, const Eigen::Vector2f& size)
{
	Collider::innit(scene, position, size);
	Transform::position = position;
	BoxRenderer::innit(Eigen::Vector2f(0.0f, 0.0f), size, Eigen::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
}

void Wall::step()
{
	Collider::setPos(Transform::position);
	BoxRenderer::Render(Transform::position);
}
