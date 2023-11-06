#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <string>
#include <vector>

#include "../Mesh/mesh.h"
#include "../shader.h"

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class GameObject;

class Component
{
public:
	std::string id;
	GameObject* gameObject;

	Component(std::string id) 
	{
		this->id = id;
		gameObject = nullptr;
	}

	virtual void Start() = 0;

	virtual void Update(float dt) = 0;
};

class GameObject
{
public:
	GameObject(std::string name)
	{
		this->name = name;
		this->transform = {};
		this->transform.position = glm::vec3(0.0f);
		this->transform.rotation = glm::vec3(0.0f);
		this->transform.scale = glm::vec3(1.0f);
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

	void addComponent(Component* com)
	{
		components[com->id] = com;
		com->gameObject = this;		
	}

	void AddMesh(Mesh* mesh)
	{
		meshes.push_back(mesh);
	}

	Transform* GetTransform() { return &transform; }

	void Start()
	{
		for (auto c = components.begin(); c != components.end(); c++)
		{
			c->second->Start();
		}
	}

	virtual void Update(float dt)
	{
		for (auto c = components.begin(); c != components.end(); c++)
		{
			c->second->Update(dt);
		}
	}

	void Render(Shader* shader)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, transform.rotation.x, {1, 0, 0});
		model = glm::rotate(model, transform.rotation.y, {0, 1, 0 });
		model = glm::rotate(model, transform.rotation.z, {0, 0, 1 });
		model = glm::scale(model, transform.scale);
		shader->setMat4("model", model);

		for (Mesh* m : meshes)
		{
			m->Draw();
		}
	}

private:
	std::string name;
	std::unordered_map<std::string, Component*> components;
	std::vector<Mesh*> meshes;
	Transform transform;
};