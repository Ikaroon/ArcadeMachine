#pragma once
#include "ECS.h"
#include "stdafx.h"

class Scene
{
public:
	Scene();
	~Scene();

	std::vector<GameObject*>* get_AllGameObjects() { return &m_GameObjects; }
	std::vector<Component*>* get_AllComponents() { return &m_Components; }
	std::vector<System*>* get_AllSystems() { return &m_Systems; }

	void add_GameObject(GameObject* gameObject) { m_GameObjects.push_back(gameObject); }
	void add_Component(Component* component) { m_Components.push_back(component); }
	void add_System(System* system) { m_Systems.push_back(system); }

	//template <class T>
	//std::vector<T*> get_Components() const;
protected:
	std::vector<GameObject*> m_GameObjects;
	std::vector<Component*> m_Components;
	std::vector<System*> m_Systems;
};
/*
template <typename T>
std::vector<Component*> Scene::get_Components() const {
	std::vector<Component*> components;
	for (auto i = m_Components.begin(); i < m_Components.end(); ++i) {
		Component* comp = dynamic_cast<Component*> (*i);
		if (comp != nullptr) components.push_back(comp);
	}
	return components;
}*/