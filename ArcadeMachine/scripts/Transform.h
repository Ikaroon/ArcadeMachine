#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc\quaternion.hpp>
#include <gtx\quaternion.hpp>

class Transform
{
public:
	glm::vec3 m_LocalPosition;
	glm::quat m_LocalRotation;
	glm::vec3 m_LocalScale;

	Transform()
	{
		m_LocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		m_LocalRotation = glm::quat();
		m_LocalScale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	explicit Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
	{
		m_LocalPosition = pos;
		m_LocalRotation = glm::quat(rot);
		m_LocalScale = scale;
	}

	virtual ~Transform()
	{

	}

	void setParent(Transform* parent)
	{
		m_Parent = parent;
	}

	// Transformation

	void translateLocal(glm::vec3 translation)
	{
		m_LocalPosition += translation;
	}

	glm::vec3 get_Position() const
	{
		if (m_Parent == nullptr)
		{
			return m_LocalPosition;
		}
		return m_Parent->m_LocalRotation * (m_LocalPosition /* m_Parent->m_LocalScale*/) + m_Parent->get_Position();
	}

	glm::mat4x4 get_TranslationMatrix() const
	{
		glm::vec3 position = get_Position();
		return glm::translate(glm::mat4(1.0f), position);
	}

	// Scale

	void scaleLocal(const glm::vec3 scaling)
	{
		m_LocalScale *= scaling;
	}

	glm::mat4x4 get_ScaleMatrix() const
	{
		const glm::vec3* s = &m_LocalScale; // making a pointer for less writing
		glm::mat4x4 mat(	glm::mat4::col_type(s->x, 0.0f,	0.0f, 0.0f),
							glm::mat4::col_type(0.0f, s->y,	0.0f, 0.0f),
							glm::mat4::col_type(0.0f, 0.0f,	s->z, 0.0f),
							glm::mat4::col_type(0.0f, 0.0f,	0.0f, 1.0f));
		return mat;
	}

	// Rotation

	void rotateLocal(const glm::quat rotation)
	{
		m_LocalRotation *= rotation;
	}

	void rotateLocal(const glm::vec3 rotation)
	{
		rotateLocal(glm::quat(rotation));
	}

	void rotateLocal(const float x, const float y, const float z)
	{
		rotateLocal(glm::vec3(x, y, z));
	}

	glm::vec3 get_LocalEulerAngles() const
	{
		return glm::eulerAngles(m_LocalRotation);
	}

	void set_LocalEulerAngles(glm::vec3 rotation)
	{
		m_LocalRotation = glm::quat(glm::radians(rotation));
	}

	void set_LocalEulerAngles(float x, float y, float z)
	{
		set_LocalEulerAngles(glm::vec3(x, y, z));
	}

	glm::quat get_Rotation() const
	{
		if (m_Parent == nullptr)
		{
			return m_LocalRotation;
		}
		return m_LocalRotation *m_Parent->get_Rotation();
	}

	glm::mat4x4 get_RotationMatrix() const
	{
		return glm::toMat4(m_LocalRotation);
	}

	const Transform* ROOT = nullptr;

	// Rendering Matrices

	glm::mat4x4 get_ObjectToWorldMatrix() const
	{
		return get_TranslationMatrix() * get_RotationMatrix() * get_ScaleMatrix();
	}

	Transform* get_Parent()
	{
		return m_Parent;
	}

private:
	Transform * m_Parent;
	glm::mat4x4 m_ObjectToWorld;
};