#pragma once
#include <string>

class Object
{
public:
	std::string id;
	virtual void step() {}

	template <typename T>
	inline T* getComponent() { return dynamic_cast<T*>(this); }
};