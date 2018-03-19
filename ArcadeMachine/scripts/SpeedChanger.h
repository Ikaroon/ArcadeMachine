#pragma once
#include "ECS.h"

class SpeedChanger : public Component
{
public:
	float m_Speed;

	SpeedChanger(float speed)
	{
		m_Speed = speed;
	}
	virtual ~SpeedChanger() {};
};
