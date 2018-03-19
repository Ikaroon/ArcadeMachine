#pragma once
#include "stdafx.h"
#include "ECS.h"

class GameScreensSystem : public System
{
public:
	static GameScreensSystem* m_System;
	GameObject* m_Ready;
	GameObject* m_Go;
	GameObject* m_GameOver;

	enum class STATE { START, PLAY, GAMEOVER };
	STATE m_State;

	GameScreensSystem(GameObject* ready, GameObject* go, GameObject* gameover);
	~GameScreensSystem();

	void set_GameOver() { m_State = STATE::GAMEOVER; };
	void set_Start() { m_State = STATE::START; };

	void update();
	void lateUpdate();
private:
	float m_StartTime = 4.0f;
	bool m_Pressed = false;
};
