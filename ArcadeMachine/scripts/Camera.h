#pragma once
#include "ECS.h"
#include <gtc/matrix_transform.hpp>

class Camera : public Component
{
public:
	float m_FoV;
	float m_NearClip;
	float m_FarClip;
	glm::vec3 m_ClearColor;

	static Camera* activeCamera;

	Camera(float FoV, float nearClip, float farClip, glm::vec3 color)
	{
		m_FoV = FoV;
		m_NearClip = nearClip;
		m_FarClip = farClip;
		m_ClearColor = color;

		activeCamera = this;
	}

	virtual ~Camera() {};

	glm::mat4x4 get_ViewMatrix() const
	{
		const glm::vec3 pos = get_GameObject()->get_Transform()->get_Position();
		const glm::quat rot = get_GameObject()->get_Transform()->get_Rotation();
		const glm::vec3* scale = &get_GameObject()->get_Transform()->m_LocalScale;

		glm::mat4 view = glm::lookAt(
			pos,
			pos + (rot * glm::vec3(0.0f, 0.0f, 1.0f)),
			get_GameObject()->get_Transform()->get_Rotation() * glm::vec3(0.0f, scale->y, 0.0f)
		);

		return view;
	}

	glm::mat4x4 get_PerspectiveMatrix(float width, float height) const
	{
		return glm::perspective(glm::radians(m_FoV), (float)width / (float)height, m_NearClip, m_FarClip);
	}

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

};