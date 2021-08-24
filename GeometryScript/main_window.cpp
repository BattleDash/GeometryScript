#include "main_window.h"
#include "program.h"
#include "renderer.h"
#include "scripts_category.h"
#include "debug_category.h"
#include "imgui/imgui_text_extension.h"

GeometryScript::UI::Window::Windows::MainWindow* gMainWindow;

namespace GeometryScript::UI::Window::Windows
{
    MainWindow::MainWindow()
    {
        categories.push_back(new Main::Categories::ScriptsCategory);
#if _DEV
        categories.push_back(new Main::Categories::DebugCategory);
#endif
        //m_vCategories.push_back(new mainwindow::category::categories::PlayerCategory);
    }

    bool MainWindow::ShouldDisplay()
    {
        return isOpen;
    }
    void MainWindow::Draw()
    {
        ImGui::BeginMainMenuBar();
        {
            ImGui::Text("Geometry Script");

            for (Main::Category* category : categories)
            {
                category->Draw();
            }

            // Help remains hardcoded, because we always want it to appear last.
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    if (!gRenderer->HasWindowOfType<AboutWindow>())
                    {
                        new AboutWindow;
                    }
                    //aboutWindow->isOpen = !aboutWindow->isOpen;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
    void MainWindow::Update()
    {
        //m_bIsOpen = gRenderer->m_bLockFortInput;
    }
}