#pragma once

#include "../mesh.h"

class VerticalPlain : public Mesh
{
public:
	static VerticalPlain* GetInstance(bool isX)
	{
		if (isX)
		{
			if (!p_x_instance)
			{
				p_x_instance = new VerticalPlain(true);
			}

			return p_x_instance;
		}
		else
		{
			if (!p_z_instance)
			{
				p_z_instance = new VerticalPlain(false);
			}

			return p_z_instance;
		}
	}

private:
	static VerticalPlain* p_x_instance;
	static VerticalPlain* p_z_instance;

	VerticalPlain(bool isX) : Mesh()
	{
		if (isX)
		{
			Vertex vTL = { glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
			Vertex vTR = { glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
			Vertex vBR = { glm::vec3(0.5f, -0.5f, .0f), glm::vec3(0.0f, 0.0f, 1.0f) };
			Vertex vBL = { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };

			this->vertices = { vTL, vTR, vBR, vBL };
			this->indices = { 0, 1, 3, 3, 2, 1 };
		}
		else
		{
			Vertex vTL = { glm::vec3(0.0f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f) };
			Vertex vTR = { glm::vec3(0.0f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) };
			Vertex vBR = { glm::vec3(0.0f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f) };
			Vertex vBL = { glm::vec3(0.0f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f) };

			this->vertices = { vTL, vTR, vBR, vBL };
			this->indices = { 0, 1, 3, 3, 2, 1 };
		}

		SetupMesh();
	}
};