#pragma once

#include "category.h"

namespace GeometryScript::UI::Window::Windows::Main::Categories
{
    class ScriptsCategory : public Category
    {
    public:
        ScriptsCategory();

        void DrawButtons() override;
    };
}