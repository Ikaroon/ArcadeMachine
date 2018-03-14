#pragma once
#include "ECS.h"

class Coin : public Component
{
public:
	int m_Points;

	Coin(int points)
	{
		m_Points = points;
	}
	virtual ~Coin() {};
};