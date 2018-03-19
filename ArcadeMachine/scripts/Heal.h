#pragma once
#include "ECS.h"

class Heal : public Component
{
public:
	float m_Health;

	Heal(float health)
	{
		m_Health = health;
	}
	virtual ~Heal() {};
};