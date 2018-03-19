#include "GameScreensSystem.h"
#include "RenderSystem.h"
#include "Player.h"
#include "Application.h"
#include "Time.h"

GameScreensSystem* GameScreensSystem::m_System = nullptr;

GameScreensSystem::GameScreensSystem(GameObject * ready, GameObject * go, GameObject * gameover)
{
	m_Ready = ready;
	m_GameOver = gameover;
	m_Go = go;
	m_State = STATE::START;
	m_System = this;
}

GameScreensSystem::~GameScreensSystem()
{
}

void GameScreensSystem::update()
{
	switch (m_State)
	{
		case STATE::PLAY:
		{
			return;
		}
		break;
		case STATE::START:
		{
			m_StartTime -= Time::get_DeltaTime();
			m_GameOver->get_Transform()->m_LocalPosition.y = 10.0f;
			if (m_StartTime >= 1.0f)
			{
				m_Ready->get_Transform()->m_LocalPosition.y = 0.0f;
			}
			else if (m_StartTime > 0.0f)
			{
				m_Ready->get_Transform()->m_LocalPosition.y = 10.0f;
				m_Go->get_Transform()->m_LocalPosition.y = 0.0f;
			}
			else
			{
				m_Ready->get_Transform()->m_LocalPosition.y = 10.0f;
				m_Go->get_Transform()->m_LocalPosition.y = 10.0f;
				m_StartTime = 4.0f;
				m_State = STATE::PLAY;
			}
		}
		break;
		case STATE::GAMEOVER:
		{
			m_GameOver->get_Transform()->m_LocalPosition.y = 0.0f;
			if (RenderSystem::get_Window()->get_Key(GLFW_KEY_R) == GLFW_PRESS)
			{
				m_Pressed = true;
			}

			if (RenderSystem::get_Window()->get_Key(GLFW_KEY_R) == GLFW_RELEASE && m_Pressed) {
				Application::loadScene(0);
			}
		}
		break;
	}
}

void GameScreensSystem::lateUpdate()
{
}
