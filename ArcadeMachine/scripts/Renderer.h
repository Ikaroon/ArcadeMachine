#pragma once
#include "Component.h"
#include "RenderPackage.h"

class Renderer : public Component
{
public:
	Renderer() {};
	virtual ~Renderer()
	{
	};

	virtual RenderPackage get_RenderData()
	{
		RenderPackage package = {
			m_Mesh, // The mesh for the package
			m_Material // The material for the package
		};
		return package;
	};
protected:
	Mesh* m_Mesh;
	Material* m_Material;
};