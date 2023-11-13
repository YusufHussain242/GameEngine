#pragma once
#include "../Scenes/Scene.h"
#include <Eigen/Dense>

struct Segment
{
	Segment() = default;

	Segment(const Eigen::Vector2f& _position, const Eigen::Vector2f& _direction, float _length)
		: position(_position), direction(_direction), length(_length) {}
	Eigen::Vector2f position;
	Eigen::Vector2f direction;
	float length;
};

struct CollisionData
{
	std::vector<Object*> objects;
};

struct RaycastData
{
	Object* object;
	const Segment* segment;
	float distance;
};


class Collider
{
private:
	Eigen::Vector2f m_size;
	Eigen::Vector2f m_position;
	Segment m_segments[4];
	Scene* m_scene;
public:
	void innit(Scene* scene, const Eigen::Vector2f& position, const Eigen::Vector2f& size);

	bool isColliding(const Eigen::Vector2f& offset);

	bool isColliding(const Eigen::Vector2f& offset, const std::vector<Object*>& objects);

	bool getCollisionData(const Eigen::Vector2f& offset, CollisionData& out);

	inline void setPos(const Eigen::Vector2f& pos)
	{ 
		m_position = pos;
		calculateSegments();
	}

	inline const Eigen::Vector2f& getPos() const
	{ return m_position; }
	
	inline void setSize(const Eigen::Vector2f& size)
	{ 
		m_size = size;
		calculateSegments();
	}

	inline const Eigen::Vector2f& getSize() const
	{ return m_size; }

	void calculateSegments();

	inline const Segment& getSegment(unsigned int index) const
	{ return m_segments[index]; }

	bool rayCast(const Eigen::Vector2f& position, Eigen::Vector2f direction, RaycastData& out);

	bool rayCast(const Eigen::Vector2f& position, Eigen::Vector2f direction, float distance, RaycastData& out);

	bool rayCast(const Eigen::Vector2f& position, Eigen::Vector2f direction, const std::vector<Object*>& objects, RaycastData& out);

	bool rayCast(const Eigen::Vector2f& position, Eigen::Vector2f direction, float distance, const std::vector<Object*>& objects, RaycastData& out);
};