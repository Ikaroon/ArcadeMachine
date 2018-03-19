#include "ItemController.h"
#include "Application.h"
#include "Bomb.h"
#include "Coin.h"
#include "Heal.h"
#include "SpeedChanger.h"
#include "Player.h"
#include "Time.h"
#include "Camera.h"

ItemController::ItemController(Material * health, Material * score1, Material * score10, Material * score100)
{
	healthMat = health;
	score1Mat = score1;
	score10Mat = score10;
	score100Mat = score100;
	Debug::log("Started: Item System");
}

ItemController::~ItemController()
{
	Debug::log("Shut off: Item System");
}

void ItemController::update()
{
	if (Camera::activeCamera == nullptr)
	{
		return;
	}

	std::vector<Component*>* m_Components = Application::get_CurrentScene()->get_AllComponents();

	float upperEnd = abs(Camera::activeCamera->get_GameObject()->get_Transform()->m_LocalPosition.z) * tan(Camera::activeCamera->m_FoV / 2);

	for (unsigned int c = 0; c < m_Components->size(); c++)
	{
		// Check if bomb
		Bomb* bomb = dynamic_cast<Bomb*>((*m_Components)[c]);
		if (bomb != nullptr)
		{
			bomb->get_GameObject()->get_Transform()->m_LocalPosition.y += Player::m_Player->m_FallSpeed * 0.3f * Time::get_DeltaTime();

			if (bomb->get_GameObject()->get_Transform()->m_LocalPosition.y >(upperEnd + 0.025f))
			{
				srand(time(0) + rand());
				float lerpVal = (rand() % 1001) / 1000.0f;
				bomb->get_GameObject()->get_Transform()->m_LocalPosition.x = glm::mix(-0.5f, 0.5f, lerpVal);
				bomb->get_GameObject()->get_Transform()->m_LocalPosition.y = -(upperEnd + 0.025f);
			}
		}

		// Check if coin
		Coin* coin = dynamic_cast<Coin*>((*m_Components)[c]);
		if (coin != nullptr)
		{
			coin->get_GameObject()->get_Transform()->m_LocalPosition.y += Player::m_Player->m_FallSpeed * 0.3f * Time::get_DeltaTime();

			if (coin->get_GameObject()->get_Transform()->m_LocalPosition.y > (upperEnd + 0.025f))
			{
				srand(time(0) + rand());
				float lerpVal = (rand() % 1001) / 1000.0f;
				coin->get_GameObject()->get_Transform()->m_LocalPosition.x = glm::mix(-0.5f, 0.5f, lerpVal);
				coin->get_GameObject()->get_Transform()->m_LocalPosition.y = -(upperEnd + 0.025f);
			}
		}

		// Check if heal
		Heal* heal = dynamic_cast<Heal*>((*m_Components)[c]);
		if (heal != nullptr)
		{
			heal->get_GameObject()->get_Transform()->m_LocalPosition.y += Player::m_Player->m_FallSpeed * 0.3f * Time::get_DeltaTime();

			if (heal->get_GameObject()->get_Transform()->m_LocalPosition.y > (upperEnd + 0.025f))
			{
				srand(time(0) + rand());
				float lerpVal = (rand() % 1001) / 1000.0f;
				heal->get_GameObject()->get_Transform()->m_LocalPosition.x = glm::mix(-0.5f, 0.5f, lerpVal);
				heal->get_GameObject()->get_Transform()->m_LocalPosition.y = -(upperEnd + 0.025f + rand() % 100);
			}
		}

		// Check if speedChanger
		SpeedChanger* speedChanger = dynamic_cast<SpeedChanger*>((*m_Components)[c]);
		if (speedChanger != nullptr)
		{
			speedChanger->get_GameObject()->get_Transform()->m_LocalPosition.y += Player::m_Player->m_FallSpeed * 0.3f * Time::get_DeltaTime();

			if (speedChanger->get_GameObject()->get_Transform()->m_LocalPosition.y > (upperEnd + 0.025f))
			{
				srand(time(0) + rand());
				float lerpVal = (rand() % 1001) / 1000.0f;
				speedChanger->get_GameObject()->get_Transform()->m_LocalPosition.x = glm::mix(-0.5f, 0.5f, lerpVal);
				speedChanger->get_GameObject()->get_Transform()->m_LocalPosition.y = -(upperEnd + 0.025f + rand() % 100);
			}
		}
	}
}

void ItemController::lateUpdate()
{
	if (Camera::activeCamera == nullptr)
	{
		return;
	}

	std::vector<Component*>* m_Components = Application::get_CurrentScene()->get_AllComponents();

	for (unsigned int c = 0; c < m_Components->size(); c++)
	{
		// Check if bomb
		Bomb* bomb = dynamic_cast<Bomb*>((*m_Components)[c]);
		if (bomb != nullptr)
		{
			float distance = glm::distance(bomb->get_GameObject()->get_Transform()->m_LocalPosition, Player::m_Player->get_GameObject()->get_Transform()->m_LocalPosition);

			if (distance < 0.05f)
			{
				Player::m_Player->m_Health -= bomb->m_Damage;
				Player::m_Player->m_Health = glm::min(1.0f, Player::m_Player->m_Health);
				healthMat->setVector("_Fill", glm::vec2(Player::m_Player->m_Health, 0));
				bomb->get_GameObject()->get_Transform()->m_LocalPosition.y += 10.0f;
			}
		}

		// Check if coin
		Coin* coin = dynamic_cast<Coin*>((*m_Components)[c]);
		if (coin != nullptr)
		{
			float distance = glm::distance(coin->get_GameObject()->get_Transform()->m_LocalPosition, Player::m_Player->get_GameObject()->get_Transform()->m_LocalPosition);

			if (distance < 0.04f)
			{
				Player::m_Player->m_Score += coin->m_Points;
				score1Mat->setInt("_TexPos", floor(Player::m_Player->m_Score % 10));
				score10Mat->setInt("_TexPos", (int)floor(Player::m_Player->m_Score / 10) % 10);
				score100Mat->setInt("_TexPos", (int)floor(Player::m_Player->m_Score / 100) % 10);
				coin->get_GameObject()->get_Transform()->m_LocalPosition.y += 10.0f;
			}
		}

		// Check if heal
		Heal* heal = dynamic_cast<Heal*>((*m_Components)[c]);
		if (heal != nullptr)
		{
			float distance = glm::distance(heal->get_GameObject()->get_Transform()->m_LocalPosition, Player::m_Player->get_GameObject()->get_Transform()->m_LocalPosition);

			if (distance < 0.05f)
			{
				Player::m_Player->m_Health += heal->m_Health;
				Player::m_Player->m_Health = glm::min(1.0f, Player::m_Player->m_Health);
				healthMat->setVector("_Fill", glm::vec2(Player::m_Player->m_Health, 0));
				heal->get_GameObject()->get_Transform()->m_LocalPosition.y += 10.0f;
			}
		}

		// Check if speedChanger
		SpeedChanger* speedChanger = dynamic_cast<SpeedChanger*>((*m_Components)[c]);
		if (speedChanger != nullptr)
		{
			float distance = glm::distance(speedChanger->get_GameObject()->get_Transform()->m_LocalPosition, Player::m_Player->get_GameObject()->get_Transform()->m_LocalPosition);

			if (distance < 0.05f)
			{
				Player::m_Player->m_FallSpeed *= speedChanger->m_Speed;
				speedChanger->get_GameObject()->get_Transform()->m_LocalPosition.y += 10.0f;
			}
		}
	}

	if (Player::m_Player->m_Health <= 0.0f)
	{
		Application::loadScene(0);
	}
}
