#include "renderer.h"
#include "window.h"
#include "main_window.h"

namespace GeometryScript
{
    namespace UI
    {
        namespace Window
        {
            UIWindow::UIWindow()
            {
                gRenderer->uiWindows.push_back(this);
            }
            void UIWindow::Remove()
            {
                gRenderer->uiWindows.erase(std::remove(gRenderer->uiWindows.begin(), gRenderer->uiWindows.end(), this), gRenderer->uiWindows.end());
                delete this;
            }
            bool UIWindow::ShouldDisplay()
            {
                return isOpen && gMainWindow->ShouldDisplay();
            }
            void UIWindow::Draw()
            {
            }
            void UIWindow::Resize()
            {
            }
            void UIWindow::Update()
            {
            }
        }
    }
}