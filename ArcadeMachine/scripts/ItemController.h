#pragma once
#include "stdafx.h"
#include "ECS.h"
#include "Material.h"

class ItemController : public System
{
public:

	ItemController(Material* health, Material* score1, Material* score10, Material* score100);
	~ItemController();

	void update();
	void lateUpdate();
private:
	Material* healthMat;
	Material* score1Mat;
	Material* score10Mat;
	Material* score100Mat;
};
