#include "about_window.h"
#include "imgui/imgui_text_extension.h"
#include "build.h"

#include <string>

namespace GeometryScript::UI::Window::Windows
{
	void AboutWindow::Draw()
	{
		std::string verNum = GEOMETRY_SCRIPT_VER;
		std::string verEnv = GEOMETRY_SCRIPT_ID;
		std::string combined = verNum + "-" + verEnv;

		ImGui::SetNextWindowSize(ImVec2(370, 650));
		ImGui::Begin("About", &isOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		{
			ImGui::Header("Geometry Script");
			ImGui::SameLine();

			ImGui::Header(ImVec4(1.0f, 1.0f, 1.0f, 0.15f), combined.c_str());

			ImGui::SmallText("TBD.");

			ImGui::Dummy(ImVec2(1, 10));

			ImGui::Header2("Lead Developer");
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.6f), "BattleDash");

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
