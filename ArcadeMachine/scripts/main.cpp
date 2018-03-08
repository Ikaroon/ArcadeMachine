#include "Application.h"
#include <windows.h>

int main()
{
	#if _DEBUG
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_EXTENDED_FLAGS);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS);
	#else
	FreeConsole();
	#endif

	// Start Application
	Application* app = Application::instance();
	int a = app->update();

	// Delete app;
	#if _DEBUG
	while (true)
	{
		// Wait until the console is closed
	}
	#endif

	return 0;
}