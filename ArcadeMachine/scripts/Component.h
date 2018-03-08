#pragma once
#include "GameObject.h"

class Component
{
public:
	virtual ~Component() {};

	void set_GameObject(class GameObject* gameObject) { m_GameObject = gameObject; }
	class GameObject* get_GameObject() const { return m_GameObject; }
private:
	class GameObject* m_GameObject;

};