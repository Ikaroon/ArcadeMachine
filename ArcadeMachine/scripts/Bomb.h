#pragma once
#include "ECS.h"

class Bomb : public Component
{
public:
	float m_Damage;

	Bomb(float damage)
	{
		m_Damage = damage;
	}
	virtual ~Bomb() {};
};