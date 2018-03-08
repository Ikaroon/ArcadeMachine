#include "Time.h"

Time* Time::INSTANCE = 0;

Time::Time()
{
	startFrameTime = get_Time();
	lastFrameTime = startFrameTime;
	timeScale = 1.0f;
}

Time::~Time()
{
	std::cout << "Shut off: Time System" << std::endl;
}


float Time::get_LastTime()
{
	return instance()->lastFrameTime;
}

float Time::get_Time()
{
	// Here comes the connection to the system time
	return (float)(clock()) / 1000;
}


float Time::get_TimeSinceStart()
{
	return instance()->get_TimeSinceStartLocal();
}

float Time::get_TimeSinceStartLocal()
{
	return lastFrameTime - startFrameTime;
}


float Time::get_DeltaTime()
{
	return instance()->get_DeltaTimeLocal();
}

float Time::get_DeltaTimeLocal()
{
	return get_DeltaTimeUnscaledLocal() * timeScale;
}


float Time::get_DeltaTimeUnscaled()
{
	return instance()->get_DeltaTimeUnscaledLocal();
}

float Time::get_DeltaTimeUnscaledLocal()
{
	return deltaTime;
}


float Time::get_TimeScale()
{
	return instance()->get_TimeScaleLocal();
}

float Time::get_TimeScaleLocal()
{
	return timeScale;
}


void Time::set_TimeScale(float scale)
{
	instance()->set_TimeScaleLocal(scale);
}

void Time::set_TimeScaleLocal(float scale)
{
	timeScale = scale;
}


std::string Time::log()
{
	return std::string("DT: " + std::to_string(get_DeltaTime()) + " | DTU: " + std::to_string(get_DeltaTimeUnscaled()) + " | Time: " + std::to_string(get_Time()));
}

void Time::update()
{
	float currentTime = get_Time();

	deltaTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;

	//Debug::log(log());
}
