#include "Scene.h"

void Scene::step()
{
	for (Object* object : objects)
	{
		object->step();
	}
}

void Scene::instantiate(Object& object) { objects.push_back(&object); }
