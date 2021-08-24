#include "category.h"

#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_internal.h"
#include <iostream>

namespace GeometryScript::UI::Window::Windows::Main
{
    void Category::DrawButtons()
    {
    }

    void Category::Draw()
    {
        if (ImGui::BeginMenu(categoryName))
        {
            for (auto& category : categories)
            {
                category->Draw();
            }
            DrawButtons();
            ImGui::EndMenu();
        }
    }
}