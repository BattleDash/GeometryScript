#include "debug_category.h"
#include "debug_window.h"
#include "renderer.h"
#include "node_manager.h"

namespace GeometryScript::UI::Window::Windows::Main::Categories
{
	DebugCategory::DebugCategory()
	{
		categoryName = "Debug";
	}

	void DebugCategory::DrawButtons()
	{
		if (ImGui::MenuItem("Execution Manager"))
		{
			if (!gRenderer->HasWindowOfType<DebugWindow>())
			{
				new DebugWindow;
			}
		}
		if (ImGui::MenuItem("Create Executor Instance"))
		{
			gNodeManager->CreateInstance();
		}
	}
}