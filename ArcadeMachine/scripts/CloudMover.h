#pragma once
#include "stdafx.h"
#include "ECS.h"

class CloudMover : public System
{
public:
	CloudMover();
	~CloudMover();

	void update();
};
