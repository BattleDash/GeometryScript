#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_internal.h"

namespace GeometryScript
{
    namespace UI
    {
        namespace Window
        {
            //!  Base class for an ImGui window.
            /*!
             * Contains functions like Draw, Resize and Update, called by the UIRenderer.
             */
            class UIWindow
            {
            public:
                bool isOpen = true;

                UIWindow();

                virtual bool ShouldDisplay();
                virtual void Remove();
                virtual void Draw(); //!< Draw is called each tick while the window is open.
                virtual void Resize(); //!< Resize is called when the Geometry Dash window is resized, regardless of the window being open or closed.
                virtual void Update(); //!< Update is called each tick, regardless of the window being open or closed.
            };
        }
    }
}
