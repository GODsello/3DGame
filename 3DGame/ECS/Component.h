#pragma once

#include <string>


class Component
{
public:
	std::string id;

	void Start() {};

	virtual void Update(float dt) = 0;
};