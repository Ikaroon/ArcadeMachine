#pragma once
#include "stdafx.h"
#include "ECS.h"

class ItemController : public System
{
public:
	ItemController();
	~ItemController();

	void update();
	void lateUpdate();
};
