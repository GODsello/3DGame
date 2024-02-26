#pragma once

#include "../mesh.h"

class HorizontalPlain : public Mesh
{
public:
	static HorizontalPlain* GetInstance()
	{
		if (!p_instance)
		{
			p_instance = new HorizontalPlain();
		}

		return p_instance;
	}

private:
	static HorizontalPlain* p_instance;

	HorizontalPlain() : Mesh()
	{
		Vertex vTL = { glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f) };
		Vertex vTR = { glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f) };
		Vertex vBR = { glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f) };
		Vertex vBL = { glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f) };

		this->vertices = { vTL, vTR, vBR, vBL };
		this->indices = { 0, 1, 3, 3, 2, 1 };

		SetupMesh();
	}
};