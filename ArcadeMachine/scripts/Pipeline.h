#pragma once
#include "stdafx.h"
#include "ECS.h"

namespace pipeline {
	const float FIXED_TIME_STEP = 0.2f;
	static float lastFixedTimeStamp;
	static void updateAll(std::vector<System*>& systems)
	{
		// Do the pipeline
		if (abs(lastFixedTimeStamp - Time::get_TimeSinceStart()) >= FIXED_TIME_STEP)
		{
			lastFixedTimeStamp = Time::get_TimeSinceStart();
			for (auto i = systems.begin(); i < systems.end(); ++i) {
				System* system = dynamic_cast<System*> (*i);
				if (system != nullptr) {
					system->fixedUpdate();
				}
			}
		}
		for (auto i = systems.begin(); i < systems.end(); ++i) {
			System* system = dynamic_cast<System*> (*i);
			if (system != nullptr) {
				system->update();
			}
		}
		for (auto i = systems.begin(); i < systems.end(); ++i) {
			System* system = dynamic_cast<System*> (*i);
			if (system != nullptr) {
				system->lateUpdate();
			}
		}
		for (auto i = systems.begin(); i < systems.end(); ++i) {
			System* system = dynamic_cast<System*> (*i);
			if (system != nullptr) {
				system->onPreRender();
			}
		}
		for (auto i = systems.begin(); i < systems.end(); ++i) {
			System* system = dynamic_cast<System*> (*i);
			if (system != nullptr) {
				system->onRender();
			}
		}
		for (auto i = systems.begin(); i < systems.end(); ++i) {
			System* system = dynamic_cast<System*> (*i);
			if (system != nullptr) {
				system->onPostRender();
			}
		}
	}
}