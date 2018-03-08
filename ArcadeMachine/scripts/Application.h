#pragma once
#include "stdafx.h"
#include "Scene.h"

class Application
{
public:
	~Application();
	static Application* instance()
	{
		static CGuard g;   // Dealocation
		if (!MAIN)
			MAIN = new Application();
		return MAIN;
	}
	int update();

	static void close();
	static void loadScene(const int sceneID);

	void closeThis();
	void loadSceneInThis(const int sceneID);

	static Scene* get_CurrentScene() { return MAIN->get_CurrentSceneInThis(); }
	Scene* get_CurrentSceneInThis() { return m_CurrentScene; }
private:
	Application();
	Application(const Application&);
	static Application* MAIN;

	enum class status { RUNNING, CLOSE, LOADING };
	status m_ApplicationStatus;

	Scene* m_CurrentScene;
	int m_SceneToLoad;

	std::vector<System*> m_engineSystems;
	std::vector<System*> m_AllSystems;

	static Scene* fetchScene(const int sceneID);

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != Application::MAIN)
			{
				delete Application::MAIN;
				Application::MAIN = NULL;
			}
		}
	};
};
