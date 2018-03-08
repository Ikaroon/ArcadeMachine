#include "Application.h"
#include "EngineSystems.h"
#include "Pipeline.h"

#include "TestScene.h"

Application* Application::MAIN = 0;

Application::Application()
{

	m_engineSystems = {
		new RenderSystem()
	};

	loadSceneInThis(0);
}

Application::~Application()
{
	for (auto i = m_engineSystems.begin(); i < m_engineSystems.end(); ++i) {
		delete *i;
	}
	delete m_CurrentScene;
}

int Application::update()
{
	while (m_ApplicationStatus != status::CLOSE)
	{
		if (Time::get_Time() - Time::get_LastTime() <= (1.0f / 60.0f))
		{
			continue;
		}

		if (m_ApplicationStatus == status::CLOSE)
		{
			Debug::log("Closing...");
		}

		switch (m_ApplicationStatus)
		{
			case status::RUNNING:
			{
				pipeline::updateAll(m_AllSystems);
			}
			break;

			case status::LOADING:
			{
				Scene* result = fetchScene(m_SceneToLoad);
				if (result != nullptr)
				{
					delete m_CurrentScene;
					m_CurrentScene = result;

					m_AllSystems.clear();
					m_AllSystems.insert(std::end(m_AllSystems), std::begin(m_engineSystems), std::end(m_engineSystems));
					m_AllSystems.insert(std::end(m_AllSystems), m_CurrentScene->get_AllSystems()->begin(), m_CurrentScene->get_AllSystems()->end());
				}
				else
				{
					Debug::error("Failed to load scene!");
				}

				if (m_CurrentScene != nullptr)
				{
					if (m_ApplicationStatus != status::CLOSE)
					{
						m_ApplicationStatus = status::RUNNING;
					}
				}
				else
				{
					close();
				}
			}
			break;
		}

		Time::instance()->update();
	}

	delete instance();

	return 0;
}

void Application::close()
{
	instance()->closeThis();
}

void Application::loadScene(const int sceneID)
{
	instance()->loadSceneInThis(sceneID);
}

void Application::closeThis()
{
	if (m_ApplicationStatus == status::CLOSE)
	{
		return;
	}
	Debug::log("Application will close");
	m_ApplicationStatus = status::CLOSE;
}

void Application::loadSceneInThis(const int sceneID)
{
	Debug::sectionBegin("Scene");
	Debug::log("Application task started: Load Scene " + std::to_string(sceneID));
	if (m_ApplicationStatus == status::CLOSE)
	{
		return;
	}
	m_SceneToLoad = sceneID;
	if (m_ApplicationStatus == status::CLOSE)
	{
		return;
	}
	m_ApplicationStatus = status::LOADING;
}

Scene* Application::fetchScene(const int sceneID)
{
	Debug::log("Application is loading scene " + std::to_string(sceneID));
	Scene* loadedScene = new TestScene();
	Debug::log("Application finished loading scene " + std::to_string(sceneID));
	Debug::sectionEnd("Scene");
	return loadedScene;
}
