#pragma once
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"

class MeshRenderer : public Renderer
{
public:
	explicit MeshRenderer(Mesh* mesh, Material* material)
	{
		m_Mesh = mesh;
		m_Material = material;
	};

	MeshRenderer(Mesh* mesh)
	{
		MeshRenderer(mesh, Material::STANDARD_MATERIAL);
	};

	virtual ~MeshRenderer()
	{

	};

};