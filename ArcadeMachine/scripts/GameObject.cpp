#include "GameObject.h"

int GameObject::CURRENT_ID = 0;

GameObject::GameObject()
{
	m_InstanceID = CURRENT_ID++;
}

GameObject::GameObject(std::string name) : GameObject()
{
	m_Name = name;
	Debug::log("Initialized (GameObject: " + std::to_string(m_InstanceID) + " " + m_Name + ")");
}

GameObject::~GameObject()
{
	Debug::log("Destroyed (GameObject: " + std::to_string(m_InstanceID) + " " + m_Name + ")");
	/*for (auto i = m_Components.begin(); i < m_Components.end(); ++i) {
		delete *i;
	}*/
}

int GameObject::get_InstanceID() const
{
	return m_InstanceID;
}
