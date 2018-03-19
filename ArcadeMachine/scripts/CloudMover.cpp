#include "CloudMover.h"
#include "Application.h"
#include "Cloud.h"
#include "Time.h"
#include "Material.h"
#include "Camera.h"
#include "Player.h"

CloudMover::CloudMover()
{
	Debug::log("Started: Cloud System");
}

CloudMover::~CloudMover()
{
	Debug::log("Shut off: Cloud System");
}

void CloudMover::update()
{
	std::vector<Component*>* m_Components = Application::get_CurrentScene()->get_AllComponents();

	for (unsigned int c = 0; c < m_Components->size(); c++)
	{
		Cloud* cloud = dynamic_cast<Cloud*>((*m_Components)[c]);
		if (cloud != nullptr)
		{
			glm::vec3 pos = cloud->get_GameObject()->get_Transform()->get_Position();
			float deg = Camera::activeCamera->m_FoV;
			float offset = ((1.0f * (cloud->get_GameObject()->get_Transform()->m_LocalScale.y / 10.0f)) + abs(pos.z) * tan(deg / 2));
			if (pos.y > offset)
			{
				// Transformated
				srand(time(0) + c + rand());

				float z = ((rand() % 51) * 0.1f + 1.0f);
				z = -(z * z);

				offset = ((abs(z / 2)) + abs(z) * tan(deg / 2));

				float x = ((float)(rand() % 2001) / 1000.0f - 1.0f) * (offset + 1);
				float y = -offset;

				cloud->get_GameObject()->get_Transform()->m_LocalPosition = glm::vec3(x, y, z);
				cloud->get_GameObject()->get_Transform()->m_LocalScale = glm::vec3(10.0f, 10.0f, 10.0f) * abs(z / 2);

				glm::vec3 color = glm::mix(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(100.0f / 255.0f, 180.0f / 255.0f, 200.0f / 255.0f), abs(z + 1.0f) / 25 * 0.6f);
				cloud->m_Material->setVector("_Color", color);
				cloud->m_Material->setInt("_TexPos", rand() % 64);
			}
			else
			{
				cloud->get_GameObject()->get_Transform()->m_LocalPosition += glm::vec3(0.0f, Player::m_Player->m_FallSpeed * 5.0f * Time::get_DeltaTime(), 0.0f);
			}
		}
	}
}
