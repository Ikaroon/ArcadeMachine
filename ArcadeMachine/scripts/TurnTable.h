#pragma once
#include "stdafx.h"
#include "ECS.h"

class TurnTable : public System
{
public:
	TurnTable();
	~TurnTable();

	void update();
};
