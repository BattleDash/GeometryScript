#pragma once

#include "window.h"

namespace GeometryScript::UI::Window::Windows
{
    class DebugWindow : public UIWindow
    {
    public:
        void Draw() override;
    };
}
