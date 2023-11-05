#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "Component.h"
#include "../Mesh/mesh.h"

class GameObject
{
public:
	GameObject(std::string name)
	{
		this->name = name;
	}

	~GameObject()
	{
		for (auto c = components.begin(); c != components.end(); ++c)
		{
			delete c->second;
		}
		components.clear();
		meshes.clear();
	}

	template <typename T>
	T* GetComponent(std::string id)
	{
		if (components.count(id) == 0)
		{
			return nullptr;
		}

		return dynamic_cast<T*>(components[id]);
	}

	void RemoveComponent(std::string id)
	{
		components.erase(id);
	}

	void addComponent(std::string id, Component* c)
	{
		components[c->id] = c;
	}

	void AddMesh(Mesh* mesh)
	{
		meshes.push_back(mesh);
	}

	void Start()
	{
		for (auto c = components.begin(); c != components.end(); ++c)
		{
			c->second->Start();
		}
	}

	void Update(float dt)
	{
		for (auto c = components.begin(); c != components.end(); ++c)
		{
			c->second->Update(dt);
		}
	}

	void Render()
	{
		for (Mesh* m : meshes)
		{
			m->Draw();
		}
	}

private:
	std::string name;
	std::unordered_map<std::string, Component*> components;
	std::vector<Mesh*> meshes;
};