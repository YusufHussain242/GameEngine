#pragma once
#include "Object.h"
#include "../Components/C_BoxRenderer.h"
#include "../Components/C_Transform.h"
#include "../Components/C_Input.h"
#include "../Components/C_Collider.h"
#include "../Scenes/Scene.h"

class Player :
	public Object,
	public Transform,
	public BoxRenderer,
	public Input,
	public Collider
{
private:
	const float m_speed = 0.01f;
	const float m_xResistance = 0.5f;
	const float m_yResistance = 0.01f;
	const float m_gravity = 0.01f;
	const float m_jumpVel = 0.12f;
	const int m_collPrecision = 10;
	Eigen::Vector2f m_velocity;
public:
	Player(Scene* scene, const Eigen::Vector2f& position);

	void step() override;
};