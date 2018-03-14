#include "PlayerController.h"
#include "RenderSystem.h"
#include "Player.h"
#include "Time.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::update()
{
	Player* player = Player::m_Player;
	Transform* transform = player->get_GameObject()->get_Transform();

	if (RenderSystem::get_Window()->get_Key(GLFW_KEY_A) == GLFW_PRESS && transform->m_LocalPosition.x > -0.5f) {
		player->m_Speed = glm::max(-1.0f, Player::m_Player->m_Speed - 0.05f);
	}
	else if (RenderSystem::get_Window()->get_Key(GLFW_KEY_D) == GLFW_PRESS && transform->m_LocalPosition.x < 0.5f) {
		player->m_Speed = glm::min(1.0f, Player::m_Player->m_Speed + 0.05f);
	}
	else {
		player->m_Speed *= 0.9f;
	}

	transform->m_LocalPosition += glm::vec3(Player::m_Player->m_Speed * Time::get_DeltaTime(), 0.0f, 0.0f);
	transform->set_LocalEulerAngles(0.0f, 0.0f, Player::m_Player->m_Speed * 25.0f);

	if (transform->m_LocalPosition.x < -0.5f || transform->m_LocalPosition.x > 0.5f)
	{
		transform->m_LocalPosition.x = glm::clamp(transform->m_LocalPosition.x, -0.5f, 0.5f);
	}
}
