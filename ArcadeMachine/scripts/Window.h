#pragma once
#include "stdafx.h"

class Window
{
public:
	Window();
	explicit Window(int width, int height);
	~Window();

	void beginRendering(glm::vec3 clearColor);
	void endRendering();
	void update();
	void close();

	int get_Width();
	int get_Height();
	int get_Key(int key) { return glfwGetKey(m_Window, key); };
private:
	int m_Width, m_Height;
	GLFWwindow* m_Window;
};