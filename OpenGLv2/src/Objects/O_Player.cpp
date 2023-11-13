#include "O_Player.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <Eigen/Dense>

float magnitudeOf(float value)
{
	if (signbit(value))
		return -value;
	else
		return value;
}

char signOf(float value)
{
	if (value > 0)
		return 1;
	else if (value == 0)
		return 0;
	else return -1;
}

Player::Player(Scene* scene, const Eigen::Vector2f& position)
	: m_velocity(0, 0)
{
	Collider::innit(scene, position, Eigen::Vector2f(128.0f / 1920.0f, 128.0f / 1024.0f));
	Transform::position = position;
	BoxRenderer::innit(Eigen::Vector2f(0, 0), Eigen::Vector2f(128.0f / 1920.0f, 128.0f / 1024.0f), Eigen::Vector4f(1, 0, 0, 1));
}

void Player::step()
{
	Collider::setPos(Transform::position);

	if (Input::isPressed(GLFW_KEY_A))
		m_velocity[0] -= m_speed;
	if (Input::isPressed(GLFW_KEY_D))
		m_velocity[0] += m_speed;
	
	m_velocity[0] -= m_velocity[0] * m_xResistance;

	if (Input::isPressed(GLFW_KEY_SPACE) && Collider::isColliding(Eigen::Vector2f(0,-0.001)))
		m_velocity[1] = m_jumpVel;
	
	m_velocity[1] -= m_gravity;
	m_velocity[1] -= m_velocity[1] * m_yResistance;
	
	Eigen::Vector2f hVelocity = Eigen::Vector2f(m_velocity[0], 0);
	Eigen::Vector2f vVelocity = Eigen::Vector2f(0, m_velocity[1]);
	
	CollisionData collData;
	if (Collider::getCollisionData(hVelocity, collData))
	{
		Eigen::Vector2f decrement = hVelocity / m_collPrecision;
		hVelocity -= decrement;
		while (Collider::isColliding(hVelocity, collData.objects))
			hVelocity -= decrement;
	}
	if (Collider::getCollisionData(vVelocity, collData))
	{
		Eigen::Vector2f decrement = vVelocity / m_collPrecision;
		vVelocity -= decrement;
		while (Collider::isColliding(vVelocity, collData.objects))
			vVelocity -= decrement;
	}
	m_velocity = Eigen::Vector2f(hVelocity[0], vVelocity[1]);

	Transform::translate(m_velocity);

	BoxRenderer::Render(Transform::position);
}