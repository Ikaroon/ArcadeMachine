#pragma once

class System
{
public:
	virtual ~System() {};

	virtual void awake() {};
	virtual void start() {};
	virtual void fixedUpdate() {};
	virtual void update() {};
	virtual void lateUpdate() {};
	virtual void onPreRender() {};
	virtual void onRender() {};
	virtual void onPostRender() {};
	virtual void onQuit() {};
};

