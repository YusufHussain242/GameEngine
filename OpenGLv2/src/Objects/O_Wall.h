#pragma once
#include "Object.h"
#include "../Scenes/Scene.h"
#include "../Components/C_BoxRenderer.h"
#include "../Components/C_Transform.h"
#include "../Components/C_Collider.h"
#include <Eigen/Dense>

class Wall :
	public Object,
	public BoxRenderer,
	public Transform,
	public Collider
{
public:
	Wall(Scene* scene, const Eigen::Vector2f& position, const Eigen::Vector2f& size);

	void step() override;
};