#pragma once
#include "ECS.h"
#include "Material.h"

class Cloud : public Component
{
public:
	Cloud(Material* material)
	{
		m_Material = material;
	}
	virtual ~Cloud() {};
	Material* m_Material;
};