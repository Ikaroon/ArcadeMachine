#pragma once
#include "stdafx.h"
#include "ECS.h"
#include "Window.h"

class RenderSystem : public System
{
private:
	Window* m_Window;
public:
	RenderSystem();
	~RenderSystem();

	void onPreRender();
	void onRender();
	void onPostRender();
	void onQuit();
};
