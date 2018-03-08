#pragma once
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"

typedef unsigned int uint;

class BillboardRenderer : public Renderer
{
public:
	BillboardRenderer(Material* material)
	{
		m_Mesh = new Mesh();
		m_Material = material;
	};

	explicit BillboardRenderer(const uint textureID, const Material* material)
	{
		m_Mesh = new Mesh();
		m_Material = new Material(*material);
		// TODO : Set sprite texture in material
	}

	explicit BillboardRenderer(const uint textureID)
	{
		BillboardRenderer(textureID, Material::STANDARD_MATERIAL);
	};

	virtual ~BillboardRenderer()
	{
	};

};
