#pragma once
#include "stdafx.h"
#include "ECS.h"

class PlayerController : public System
{
public:
	PlayerController();
	~PlayerController();

	void update();
};
