#include "ItemController.h"
#include "Application.h"
#include "Bomb.h"
#include "Coin.h"
#include "Player.h"
#include "Time.h"
#include "Camera.h"

ItemController::ItemController()
{
}

ItemController::~ItemController()
{
}

void ItemController::update()
{
	std::vector<Component*>* m_Components = Application::get_CurrentScene()->get_AllComponents();

	float upperEnd = abs(Camera::activeCamera->get_GameObject()->get_Transform()->m_LocalPosition.z) * tan(Camera::activeCamera->m_FoV / 2);

	for (unsigned int c = 0; c < m_Components->size(); c++)
	{
		// Check if bomb
		Bomb* bomb = dynamic_cast<Bomb*>((*m_Components)[c]);
		if (bomb != nullptr)
		{
			bomb->get_GameObject()->get_Transform()->m_LocalPosition.y += 0.3f * Time::get_DeltaTime();

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
			coin->get_GameObject()->get_Transform()->m_LocalPosition.y += 0.3f * Time::get_DeltaTime();

			if (coin->get_GameObject()->get_Transform()->m_LocalPosition.y > (upperEnd + 0.025f))
			{
				srand(time(0) + rand());
				float lerpVal = (rand() % 1001) / 1000.0f;
				coin->get_GameObject()->get_Transform()->m_LocalPosition.x = glm::mix(-0.5f, 0.5f, lerpVal);
				coin->get_GameObject()->get_Transform()->m_LocalPosition.y = -(upperEnd + 0.025f);
			}
		}
	}
}

void ItemController::lateUpdate()
{
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
				coin->get_GameObject()->get_Transform()->m_LocalPosition.y += 10.0f;
			}
		}
	}
}
