#include "geometrydash.h"
#include "main_window.h"
#include "node_manager.h"

namespace GeometryScript
{


	DWORD WINAPI UpdateThread(LPVOID lpParam)
	{

		while (1)
		{
			Sleep(1000 / 60);
		}

		return NULL;
	}

	DWORD WINAPI LoaderThread(LPVOID lpParam)
	{
		AllocConsole();

		FILE* pFile;
		freopen_s(&pFile, "CONOUT$", "w", stdout);

		printf("Initializing...\n");

		gRenderer = new UI::Renderer;
		gMainWindow = new UI::Window::Windows::MainWindow;
		gNodeManager = new Executor::NodeManager;

		printf("Initialized.\n");

		CreateThread(0, 0, UpdateThread, 0, 0, 0); // Create thread to handle input, etc...

		return 0;
	}

	GeometryDash::GeometryDash()
	{
		if (gGeometryDash != nullptr)
			GeometryScript::Utilities::ErrorUtils::ThrowException(L"Initialization failed. Please restart Geometry Dash and try again!");

		CreateThread(0, 0, LoaderThread, 0, 0, 0);
	}

	GeometryDash::~GeometryDash()
	{
		printf("Deconstructed GeometryDash\n");
	}
}