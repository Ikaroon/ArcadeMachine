#pragma once
#include "ECS.h"

class Player : public Component
{
public:
	float m_Speed;
	int m_Score;
	float m_Health;

	static Player* m_Player;
	Player()
	{
		m_Health = 10.0f;
		m_Speed = 0.0f;
		m_Score = 0;
		m_Player = this;
	}
	virtual ~Player() {};
};