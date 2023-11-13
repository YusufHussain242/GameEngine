#pragma once
#include <vector>
#include "../Objects/Object.h"

class Scene
{
public:
	std::vector<Object*> objects;
	void instantiate(Object& object);
	void step();
};