#pragma once
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"

typedef unsigned int uint;

class UIRenderer : public Renderer
{
public:
	UIRenderer(Material* material)
	{
		m_Mesh = new Mesh();
		m_Material = material;
	};

	explicit UIRenderer(const uint textureID, const Material* material)
	{
		m_Mesh = new Mesh();
		m_Material = new Material(*material);
		// TODO : Set sprite texture in material
	}

	explicit UIRenderer(const uint textureID)
	{
		UIRenderer(textureID, Material::UI_MATERIAL);
	};

	virtual ~UIRenderer()
	{
	};

};
