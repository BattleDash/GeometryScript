#include "debug_window.h"
#include "imgui/imgui_text_extension.h"
#include "build.h"
#include "node_manager.h"

#include <string>

namespace GeometryScript::UI::Window::Windows
{
	void DebugWindow::Draw()
	{
		std::string verNum = GEOMETRY_SCRIPT_VER;
		std::string verEnv = GEOMETRY_SCRIPT_ID;
		std::string combined = verNum + "-" + verEnv;

		ImGui::SetNextWindowSize(ImVec2(370, 650));
		ImGui::Begin("Debug Execution Manager", &isOpen);
		{
			if (ImGui::Button("Create Executor Instance"))
			{
				gNodeManager->CreateInstance();
			}

			for (GeometryScript::Executor::NodeInstance* instance : gNodeManager->instances)
			{
				ImGui::Header("Node Instance");
			}

			ImGui::Dummy(ImVec2(1, 10));

			ImGui::Dummy(ImVec2(260, 0));
			ImGui::SameLine();
			if (ImGui::Button("Dismiss"))
			{
				//isOpen = false;
				Remove();
			}

			ImGui::End();
		}
	}
}
