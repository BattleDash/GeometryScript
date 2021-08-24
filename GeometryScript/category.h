#pragma once

#include <vector>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_internal.h"

namespace GeometryScript::UI::Window::Windows::Main
{
    class Category
    {
    public:
        std::vector<Category*> categories;
        const char* categoryName;

        virtual void DrawButtons();
        void Draw();
    };
}