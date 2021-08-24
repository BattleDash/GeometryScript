#pragma once

#include "window.h"

namespace GeometryScript::UI::Window::Windows
{
    class AboutWindow : public UIWindow
    {
    public:
        void Draw() override;
    };
}
