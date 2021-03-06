#include "RenderSystem.h"
#include "Application.h"

#include "Camera.h" 
#include "Renderer.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Window* RenderSystem::m_Window = NULL;

RenderSystem::RenderSystem()
{
	Debug::log("Starting: Render System");
	// Initialise GLFW
	if (!glfwInit())
	{
		Debug::error("Render System: Failed to initialize GLFW");
		Application::close();
		return;
	}
	m_Window = new Window(1280, 768);

	Debug::log("Started: Render System");

	//FontManager::registerFont("standard", "fonts/arial.ttf");
}

RenderSystem::~RenderSystem()
{
	Debug::log("Shutting off: Render System");
	delete m_Window;
	Debug::log("Shut off: Render System");
}

void RenderSystem::onPreRender()
{
}

void RenderSystem::onRender()
{
	//std::vector<Renderer*> renderComponents = Application::get_CurrentScene()->get_Components<Renderer>();

	if (m_Window != nullptr)
	{
		m_Window->update();
	}
	else
	{
		return;
	}

	std::vector<Component*>* m_Components = Application::get_CurrentScene()->get_AllComponents();

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Camera* camera = Camera::activeCamera;
	if (camera != nullptr)
	{
		viewMatrix = camera->get_ViewMatrix();
		projectionMatrix = camera->get_PerspectiveMatrix(m_Window->get_Width(), m_Window->get_Height());
	}

	m_Window->beginRendering(camera->m_ClearColor);

	for (unsigned int c = 0; c < m_Components->size(); c++)
	{
		Renderer* renderer = dynamic_cast<Renderer*>((*m_Components)[c]);
		if (renderer != nullptr)
		{
			RenderPackage package = renderer->get_RenderData();
			package.material->setActive();
			glm::mat4 modelMatrix = renderer->get_GameObject()->get_Transform()->get_ObjectToWorldMatrix();
			package.material->setMVP(viewMatrix, projectionMatrix, modelMatrix);
			package.mesh->draw();
		}
	}

	m_Window->endRendering();
}

void RenderSystem::onPostRender()
{

}

void RenderSystem::onQuit()
{
	m_Window->close();
}