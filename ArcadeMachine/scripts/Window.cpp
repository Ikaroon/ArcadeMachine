#include "Window.h"
#include "Application.h"

Window::Window()
{
	Window(640, 480);
}

Window::Window(int width, int height)
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	// (In the accompanying source code, this variable is global for simplicity)
	m_Window = glfwCreateWindow(width, height, "Arcade Machine", NULL, NULL);
	if (m_Window == NULL) {
		Debug::error("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.");
		glfwTerminate();
		Application::close();
		return;
	}
	glfwMakeContextCurrent(m_Window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		Debug::error("Failed to initialize GLEW");
		Application::close();
		return;
	}

	// Define the viewport dimensions
	glViewport(0, 0, width, height);

	// Set OpenGL options
	glEnable(GL_CULL_FACE);

	Debug::log("Window opened");
}

Window::~Window()
{
	close();
	glfwDestroyWindow(m_Window);
}

void Window::beginRendering()
{
	if (m_Window == nullptr)
	{
		Debug::error("No window found!");
		Application::close();
		return;
	}
	// Clear the background as white
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::endRendering()
{
	if (m_Window == nullptr)
	{
		Debug::error("No window found!");
		Application::close();
		return;
	}
	// Display the result
	glfwSwapBuffers(m_Window);
}

void Window::update()
{
	if (m_Window == nullptr)
	{
		Debug::error("No window found!");
		Application::close();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

	// Check if the ESC key was pressed or the window was closed
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_Window) == 0)
	{
		glfwPollEvents();
	}
	else
	{
		Application::close();
	}
}

void Window::close()
{
	Debug::log("Window closed.");
	glfwSetWindowShouldClose(m_Window, 1);
	update();
}
