#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <string>
#include <vector>

#include "../Mesh/mesh.h"
#include "../shader.h"
#include "../utils/utils.h"


struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 color;
};

class GameObject;

class Component
{
public:
	std::string id;
	GameObject* p_game_object;

	Component(std::string id) 
	{
		this->id = id;
		p_game_object = nullptr;
	}

	virtual void Start() = 0;

	virtual void Update(float dt) = 0;
};

class GameObject
{
public:
	GameObject(std::string name, 
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 color = glm::vec3(1.0f))
	{
		this->name = name;
		this->transform = {};
		this->transform.position = position;
		this->transform.rotation = rotation;
		this->transform.scale = scale;
		this->transform.color = color;
		this->p_parent_gameobject = nullptr;
		this->should_remove = false;
	}

	GameObject(std::string name, GameObject* parent) : GameObject(name)
	{
		this->p_parent_gameobject = parent;
		this->transform.position = parent->GetTransform()->position;
		this->transform.rotation = parent->GetTransform()->rotation;
		this->transform.scale = parent->GetTransform()->scale;
	}

	~GameObject()
	{
		for (auto c = components.begin(); c != components.end(); ++c)
		{
			delete c->second;
		}
		components.clear();

		for (Mesh* m : meshes)
		{
			if(m && m->vertices.size() > 0) delete m;
		}
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

	void AddComponent(Component* p_com)
	{
		components[p_com->id] = p_com;
		p_com->p_game_object = this;		
	}

	void AddMesh(Mesh* p_mesh)
	{
		meshes.push_back(p_mesh);
	}

	void AddChild(GameObject* p_go)
	{
		this->child_objects.push_back(p_go);
		p_go->SetParentGameObject(this);
	}

	Transform* GetTransform() { return &transform; }

	std::string GetName() { return name; }

	std::vector<GameObject*>& GetChildGameObjects() { return child_objects; }

	bool GetShouldRemove() { return should_remove; }

	void SetPosition(glm::vec3 position)
	{
		if (p_parent_gameobject)
		{
			transform.position = p_parent_gameobject->transform.position + position;
		}
		else
		{
			transform.position = position;
		}
	}

	void SetRotation(glm::vec3 rotation)
	{
		if (p_parent_gameobject)
		{
			transform.rotation = p_parent_gameobject->transform.rotation + rotation;
		}
		else
		{
			transform.rotation = rotation;
		}
	}

	void SetScale(glm::vec3 scale)
	{
		transform.scale = scale;
	}

	void SetColor(float r, float g, float b)
	{
		GetTransform()->color = glm::vec3(r, g, b);
	}

	void SetParentGameObject(GameObject* p_go)
	{
		this->p_parent_gameobject = p_go;
	}

	void SetShouldRemove(bool val)
	{
		this->should_remove = val;
	}

	virtual void Start()
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

	void Render(Shader* p_shader)
	{
		SetRenderParameters(p_shader);

		for (Mesh* m : meshes)
		{
			m->Draw();
		}
	}

	void DestroyThis()
	{
		SetShouldRemove(true);
		for (GameObject* g : this->child_objects)
		{
			g->SetShouldRemove(true);
		}
	}

	virtual void SetRenderParameters(Shader* p_shader)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, transform.rotation.x, { 1, 0, 0 });
		model = glm::rotate(model, transform.rotation.y, { 0, 1, 0 });
		model = glm::rotate(model, transform.rotation.z, { 0, 0, 1 });
		model = glm::scale(model, transform.scale);
		p_shader->SetMat4("model", model);

		p_shader->SetVec3("gameObjectColor", transform.color);
	}

	virtual void OnCollision(GameObject* p_collision) {};

private:
	std::string name;
	bool should_remove;
	std::unordered_map<std::string, Component*> components;
	std::vector<Mesh*> meshes;
	std::vector<GameObject*> child_objects;
	GameObject* p_parent_gameobject;
	Transform transform;
};