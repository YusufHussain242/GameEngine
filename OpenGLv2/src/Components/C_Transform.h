#pragma once
#include <Eigen/Dense>

class Transform
{
public:
	Eigen::Vector2f position;
	inline void translate(const Eigen::Vector2f& displacement)
	{ position += displacement; }
};