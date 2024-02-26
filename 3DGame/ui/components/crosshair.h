#pragma once

#include "uicomponent.h"
#include "../../renderer.h"
#include "../../shader.h"

class CrossHair : public UIComponent
{
public:
	CrossHair(Renderer *renderer)
		: UIComponent(renderer)
	{
		this->position = glm::vec3(0.5f, 0.5f, -0.2f);
		this->scale = glm::vec3(5.0f, 5.0f, 1.0f);
	}
};