#pragma once
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"

typedef unsigned int uint;

class SpriteRenderer : public Renderer
{
public:
	explicit SpriteRenderer(const uint textureID, const Material* material)
	{
		m_Mesh = new Mesh();
		m_Material = new Material(*material);
		// TODO : Set sprite texture in material
	}

	SpriteRenderer(const uint textureID)
	{
		SpriteRenderer(textureID, Material::SPRITE_MATERIAL);
	};

	virtual ~SpriteRenderer()
	{
	};

};
