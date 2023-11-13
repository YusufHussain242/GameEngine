#include "C_Collider.h"

void Collider::innit(Scene* scene, const Eigen::Vector2f& position, const Eigen::Vector2f& size)
{
	m_scene = scene;
	m_position = position;
	m_size = size;
	calculateSegments();
}

bool Collider::isColliding(const Eigen::Vector2f& offset)
{
	for (Object* object : m_scene->objects)
	{
		Collider* otherCollider = object->getComponent<Collider>();
		if (otherCollider != nullptr && otherCollider != this)
		{
			if ((m_segments[2].position[0] + offset[0] > otherCollider->getSegment(0).position[0] && m_segments[2].position[1] + offset[1] > otherCollider->getSegment(0).position[1]) &&
				(m_segments[0].position[0] + offset[0] < otherCollider->getSegment(2).position[0] && m_segments[0].position[1] + offset[1] < otherCollider->getSegment(2).position[1]))
				return true;
		}
	}
	return false;
}

bool Collider::isColliding(const Eigen::Vector2f& offset, const std::vector<Object*>& objects)
{
	for (Object* object : objects)
	{
		Collider* otherCollider = object->getComponent<Collider>();
		if (otherCollider != nullptr && otherCollider != this)
		{
			if ((m_segments[2].position[0] + offset[0] > otherCollider->getSegment(0).position[0] && m_segments[2].position[1] + offset[1] > otherCollider->getSegment(0).position[1]) &&
				(m_segments[0].position[0] + offset[0] < otherCollider->getSegment(2).position[0] && m_segments[0].position[1] + offset[1] < otherCollider->getSegment(2).position[1]))
				return true;
		}
	}
	return false;
}

bool Collider::getCollisionData(const Eigen::Vector2f& offset, CollisionData& out)
{
	for (Object* object : m_scene->objects)
	{
		Collider* otherCollider = object->getComponent<Collider>();
		if (otherCollider != nullptr && otherCollider != this)
		{
			if ((m_segments[2].position[0] + offset[0] > otherCollider->getSegment(0).position[0] && m_segments[2].position[1] + offset[1] > otherCollider->getSegment(0).position[1]) &&
				(m_segments[0].position[0] + offset[0] < otherCollider->getSegment(2).position[0] && m_segments[0].position[1] + offset[1] < otherCollider->getSegment(2).position[1]))
				out.objects.push_back(object);
		}
	}
	if (out.objects.size() > 0)
		return true;
	else
		return false;
}

void Collider::calculateSegments()
{
	m_segments[0].position = Eigen::Vector2f(m_position[0] - m_size[0] / 2, m_position[1] - m_size[1] / 2);
	m_segments[1].position = Eigen::Vector2f(m_position[0] - m_size[0] / 2, m_position[1] + m_size[1] / 2);
	m_segments[2].position = Eigen::Vector2f(m_position[0] + m_size[0] / 2, m_position[1] + m_size[1] / 2);
	m_segments[3].position = Eigen::Vector2f(m_position[0] + m_size[0] / 2, m_position[1] - m_size[1] / 2);

	m_segments[0].direction = Eigen::Vector2f(0, 1);
	m_segments[1].direction = Eigen::Vector2f(1, 0);
	m_segments[2].direction = Eigen::Vector2f(0, -1);
	m_segments[3].direction = Eigen::Vector2f(-1, 0);

	m_segments[0].length = m_size[1];
	m_segments[1].length = m_size[0];
	m_segments[2].length = m_size[1];
	m_segments[3].length = m_size[0];
}

bool Collider::rayCast(const Eigen::Vector2f& position, Eigen::Vector2f direction, RaycastData& out)
{
	 direction.normalized().eval();

	for (Object* object : m_scene->objects)
	{
		Collider* otherCollider = object->getComponent<Collider>();
		if (otherCollider != nullptr && otherCollider != this)
		{
			for (int i = 0; i < 4; i++)
			{
				Eigen::Matrix<float, 2, 2> matrix;
				matrix << direction[0], -otherCollider->getSegment(i).direction[0],
						  direction[1], -otherCollider->getSegment(i).direction[1];
				matrix = matrix.inverse().eval();

				Eigen::Vector2f vector(otherCollider->getSegment(i).position[0] - position[0], otherCollider->getSegment(i).position[1] - position[1]);
				
				Eigen::Vector2f intersection = matrix * vector;

				if (intersection[1] >= 0 && intersection[0] >= 0 && intersection[1] < otherCollider->getSegment(i).length)
				{
					out.object = object;
					out.segment = &otherCollider->getSegment(i);
					out.distance = intersection[0];
					return true;
				}
			}
		}
	}
	return false;
}

bool Collider::rayCast(const Eigen::Vector2f & position, Eigen::Vector2f direction, float distance, RaycastData & out)
{
	direction = direction.normalized().eval();

	for (Object* object : m_scene->objects)
	{
		Collider* otherCollider = object->getComponent<Collider>();
		if (otherCollider != nullptr && otherCollider != this)
		{
			for (int i = 0; i < 4; i++)
			{
				Eigen::Matrix<float, 2, 2> matrix;
				matrix << direction[0], -otherCollider->getSegment(i).direction[0],
					direction[1], -otherCollider->getSegment(i).direction[1];
				matrix = matrix.inverse().eval();

				Eigen::Vector2f vector(otherCollider->getSegment(i).position[0] - position[0], otherCollider->getSegment(i).position[1] - position[1]);

				Eigen::Vector2f intersection = matrix * vector;

				if (intersection[1] >= 0 && intersection[0] >= 0 && intersection[1] < otherCollider->getSegment(i).length && intersection[0] < distance)
				{
					out.object = object;
					out.segment = &otherCollider->getSegment(i);
					out.distance = intersection[0];
					return true;
				}
			}
		}
	}
	return false;
}

bool Collider::rayCast(const Eigen::Vector2f & position, Eigen::Vector2f direction, const std::vector<Object*>& objects, RaycastData & out)
{
	direction.normalized().eval();

	for (Object* object : objects)
	{
		Collider* otherCollider = object->getComponent<Collider>();
		if (otherCollider != nullptr && otherCollider != this)
		{
			for (int i = 0; i < 4; i++)
			{
				Eigen::Matrix<float, 2, 2> matrix;
				matrix << direction[0], -otherCollider->getSegment(i).direction[0],
					direction[1], -otherCollider->getSegment(i).direction[1];
				matrix = matrix.inverse().eval();

				Eigen::Vector2f vector(otherCollider->getSegment(i).position[0] - position[0], otherCollider->getSegment(i).position[1] - position[1]);

				Eigen::Vector2f intersection = matrix * vector;

				if (intersection[1] >= 0 && intersection[0] >= 0 && intersection[1] < otherCollider->getSegment(i).length)
				{
					out.object = object;
					out.segment = &otherCollider->getSegment(i);
					out.distance = intersection[0];
					return true;
				}
			}
		}
	}
	return false;
}

bool Collider::rayCast(const Eigen::Vector2f & position, Eigen::Vector2f direction, float distance, const std::vector<Object*>& objects, RaycastData & out)
{
	direction = direction.normalized().eval();

	for (Object* object : objects)
	{
		Collider* otherCollider = object->getComponent<Collider>();
		if (otherCollider != nullptr && otherCollider != this)
		{
			for (int i = 0; i < 4; i++)
			{
				Eigen::Matrix<float, 2, 2> matrix;
				matrix << direction[0], -otherCollider->getSegment(i).direction[0],
					direction[1], -otherCollider->getSegment(i).direction[1];
				matrix = matrix.inverse().eval();

				Eigen::Vector2f vector(otherCollider->getSegment(i).position[0] - position[0], otherCollider->getSegment(i).position[1] - position[1]);

				Eigen::Vector2f intersection = matrix * vector;

				if (intersection[1] >= 0 && intersection[0] >= 0 && intersection[1] < otherCollider->getSegment(i).length && intersection[0] < distance)
				{
					out.object = object;
					out.segment = &otherCollider->getSegment(i);
					out.distance = intersection[0];
					return true;
				}
			}
		}
	}
	return false;
}