#pragma once
#include <time.h>
#include "stdafx.h"
#include "DebugObjectContext.h"

class Time : public DebugObjectContext
{
public:
	static Time* instance()
	{
		static CGuard g;   // Speicherbereinigung
		if (!INSTANCE)
			INSTANCE = new Time();
		return INSTANCE;
	}

	static float get_LastTime();
	static float get_Time();

	static float get_TimeSinceStart();
	float get_TimeSinceStartLocal();

	static float get_DeltaTime();
	float get_DeltaTimeLocal();

	static float get_DeltaTimeUnscaled();
	float get_DeltaTimeUnscaledLocal();

	static float get_TimeScale();
	float get_TimeScaleLocal();

	static void set_TimeScale(float scale);
	void set_TimeScaleLocal(float scale);

	static std::string logTime() {
		return instance()->log();
	};
	std::string log();

	void update();

private:
	Time();
	~Time();

	static Time* INSTANCE;

	float startFrameTime;
	float lastFrameTime;
	float deltaTime;
	float timeScale;

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != Time::INSTANCE)
			{
				delete Time::INSTANCE;
				Time::INSTANCE = NULL;
			}
		}
	};
};

