#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Debug::sectionBegin("Scene");
	Debug::log("Scene is deleting...");
	for (auto i = m_Systems.begin(); i < m_Systems.end(); ++i) {
		delete *i;
	}
	for (auto i = m_GameObjects.begin(); i < m_GameObjects.end(); ++i) {
		delete *i;
	}
	for (auto i = m_Components.begin(); i < m_Components.end(); ++i) {
		delete *i;
	}
	Debug::log("Scene is completly deleted!");
	Debug::sectionEnd("Scene");
}
