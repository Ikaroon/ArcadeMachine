#pragma once
#include "stdafx.h"
#include "Transform.h"
#include "Component.h"

class GameObject
{
public:
	GameObject();
	explicit GameObject(std::string name);
	virtual ~GameObject();

	Transform* get_Transform() { return &m_Transform; }
	std::string get_Name() const { return m_Name; }

	void set_Active(const bool active) { m_Active = active; }
	bool isActive() const { return m_Active; }

	Component* add_Component(Component* component);
	template <class T>
	T* get_Component() const;

	int get_InstanceID() const;
protected:
	Transform m_Transform;

	static int CURRENT_ID;
	int m_InstanceID;

	std::string m_Name;
	bool m_Active = true;

	std::vector<class Component*> m_Components;
};

inline Component* GameObject::add_Component(Component* component)
{
	Component* comp = (component);
	if (comp != nullptr)
	{
		m_Components.push_back(comp);
		(comp)->set_GameObject(this);
	}

	return component;
}

template<class T>
inline T* GameObject::get_Component() const
{
	for (auto i = m_Components.begin(); i < m_Components.end(); ++i) {
		T* component = dynamic_cast<T*> (*i);
		if (component != nullptr) return component;
	}
	return nullptr;
}
