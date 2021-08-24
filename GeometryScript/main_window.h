#pragma once

#include "window.h"
#include "about_window.h"
#include "category.h"

#include <vector>

namespace GeometryScript::UI::Window::Windows
{
    //!  The main menu bar.
    /*!
     * In charge of giving users access to the Polaris tools.
     */
    class MainWindow : public UIWindow
    {
    public:
        std::vector<Main::Category*> categories;

        MainWindow();

        bool ShouldDisplay() override;
        void Draw() override;
        void Update() override;
    };
}

extern GeometryScript::UI::Window::Windows::MainWindow* gMainWindow;