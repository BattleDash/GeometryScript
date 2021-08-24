#include "scripts_category.h"
#include "scripts_window.h"
#include "renderer.h"

namespace GeometryScript::UI::Window::Windows::Main::Categories
{
	ScriptsCategory::ScriptsCategory()
	{
		categoryName = "Scripts";
	}

	void ScriptsCategory::DrawButtons()
	{
		if (ImGui::MenuItem("All Scripts"))
		{
			if (!gRenderer->HasWindowOfType<ScriptsWindow>())
			{
				new ScriptsWindow;
			}
		}
		if (ImGui::BeginMenu("Recent Scripts"))
		{
			ImGui::EndMenu();
		}
	}
}