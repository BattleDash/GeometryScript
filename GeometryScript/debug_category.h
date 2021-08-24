#pragma once

#include "category.h"

namespace GeometryScript::UI::Window::Windows::Main::Categories
{
    class DebugCategory : public Category
    {
    public:
        DebugCategory();

        void DrawButtons() override;
    };
}