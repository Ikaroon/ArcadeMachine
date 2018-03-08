#pragma once
#include "stdafx.h"

class Window
{
public:
	Window();
	explicit Window(int width, int height);
	~Window();

	void beginRendering();
	void endRendering();
	void update();
	void close();
private:
	int m_Width, m_Height;
	GLFWwindow* m_Window;
};