#pragma once
#include "stdafx.h"
#include "ECS.h"
#include "Window.h"

class RenderSystem : public System
{
private:
	static Window* m_Window;
public:
	RenderSystem();
	~RenderSystem();

	void onPreRender();
	void onRender();
	void onPostRender();
	void onQuit();
	static Window* get_Window() { return m_Window; };
};
