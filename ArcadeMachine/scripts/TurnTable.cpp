#include "TurnTable.h"
#include "Application.h"
#include "Camera.h"
#include "Time.h"

TurnTable::TurnTable()
{
	Debug::log("Started: TurnTable System");
}

TurnTable::~TurnTable()
{
	Debug::log("Shut off: TurnTable System");
}

void TurnTable::update()
{
	std::vector<Component*>* m_Components = Application::get_CurrentScene()->get_AllComponents();

	for (unsigned int c = 0; c < m_Components->size(); c++)
	{
		Camera* camera = dynamic_cast<Camera*>((*m_Components)[c]);
		if (camera != nullptr)
		{
			Transform* parent = camera->get_GameObject()->get_Transform()->get_Parent();
			if (parent != nullptr)
			{
				parent->rotateLocal(0.0f, 0.6f * Time::get_DeltaTime(), 0.0f);
			}
		}
	}
}
