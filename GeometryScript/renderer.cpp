#include "renderer.h"

#include <Windows.h>
#include <gl/GL.h>
#include "hook_manager.h"
#include "build.h"
#include "imgui/imgui_text_extension.h"
#include "error_utils.h"
#include "directory_utils.h"
#include <tchar.h>
#include "log_macros.h"
#include "main_window.h"
#include "platform_utils.h"
#include <iostream>

GeometryScript::UI::Renderer* gRenderer;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

__declspec(dllexport) LRESULT CALLBACK WndProcHook(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::GetCurrentContext() != nullptr)
	{
		ImGuiIO io = ImGui::GetIO();
		if (Msg == WM_KEYUP && (wParam == VK_HOME))
		{
			gMainWindow->isOpen = !gMainWindow->isOpen;
		}

		if (io.WantCaptureKeyboard || io.WantCaptureMouse)
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, Msg, wParam, lParam);
			return TRUE;
		}
	}
	return CallWindowProc(gRenderer->origWndProcFunc, hWnd, Msg, wParam, lParam);
}

bool __stdcall wglSwapBuffers(_In_ HDC hdc)
{
	static const auto trampoline = GeometryScript::Hooks::call(wglSwapBuffers);
	static HGLRC customContext;
	if (GetAsyncKeyState(VK_INSERT))
	{
		if (false && customContext != NULL)
		{
			ImGui_ImplOpenGL2_Shutdown();
			//ImGui::DestroyContext();
			wglDeleteContext(customContext);
			customContext = NULL;
			printf("Set customContext to null\n");
			//ImGui_ImplWin32_Shutdown();
			//ImGui_ImplOpenGL2_Shutdown();
			Sleep(1000);
		}
		else {
			if (customContext != NULL)
			{
				wglDeleteContext(customContext);
				customContext = NULL;
				ImGui_ImplWin32_Shutdown();
				ImGui_ImplOpenGL2_Shutdown();
			}
			customContext = wglCreateContext(hdc);
			printf("Initializing wglSwapBuffers\n");
			IMGUI_CHECKVERSION();
			printf("Setting theme\n");
			HWND origHwnd = gRenderer->hWnd;
			ImGui_ImplWin32_Init(gRenderer->hWnd = FindWindowA(NULL, "Geometry Dash"));
			ImGui_ImplOpenGL2_Init();
			//if (gRenderer->origWndProcFunc != nullptr)
			{
				//ImGui_ImplOpenGL2_CreateDeviceObjects();
			}
			if (origHwnd != gRenderer->hWnd)
			{
				gRenderer->origWndProcFunc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(gRenderer->hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcHook)));
			}
			printf("Initialized wglSwapBuffers\n");
			Sleep(1000);
		}
	}
	if (customContext != NULL)
	{
		HGLRC gameContext = wglGetCurrentContext();
		wglMakeCurrent(hdc, customContext);

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		for (GeometryScript::UI::Window::UIWindow* window : gRenderer->uiWindows)
		{
			window->Update();

			if (window->ShouldDisplay())
				window->Draw();
		}

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		wglMakeCurrent(hdc, gameContext);
	}
	return trampoline(hdc);
}

namespace GeometryScript
{
	namespace UI
	{
		void Renderer::SetTheme()
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGuiStyle* style = &ImGui::GetStyle();

			// Segoe UI font
			io.Fonts->AddFontFromFileTTF(Utilities::DirectoryUtils::GetConcatPath(Utilities::DirectoryUtils::GetFontsDir(), "segoeui.ttf").c_str(), 20);
			io.Fonts->AddFontFromFileTTF(Utilities::DirectoryUtils::GetConcatPath(Utilities::DirectoryUtils::GetFontsDir(), "segoeui.ttf").c_str(), 15);

			// Headers
			io.Fonts->AddFontFromFileTTF(Utilities::DirectoryUtils::GetConcatPath(Utilities::DirectoryUtils::GetFontsDir(), "segoeui.ttf").c_str(), 35);
			io.Fonts->AddFontFromFileTTF(Utilities::DirectoryUtils::GetConcatPath(Utilities::DirectoryUtils::GetFontsDir(), "segoeuib.ttf").c_str(), 25);

			// Bold font
			auto font = io.Fonts->AddFontFromFileTTF(Utilities::DirectoryUtils::GetConcatPath(Utilities::DirectoryUtils::GetFontsDir(), "segoeuib.ttf").c_str(), 20);

			constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
			{
				return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
			};

			style->WindowPadding = ImVec2(15, 15);
			style->WindowRounding = 5.0f;
			style->FramePadding = ImVec2(5, 5);
			style->FrameRounding = 4.0f;
			style->ItemSpacing = ImVec2(12, 8);
			style->ItemInnerSpacing = ImVec2(8, 6);
			style->IndentSpacing = 25.0f;
			style->ScrollbarSize = 15.0f;
			style->ScrollbarRounding = 9.0f;
			style->GrabMinSize = 5.0f;
			style->GrabRounding = 3.0f;

			style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
			style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
			style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
			style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
			style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		}

		Renderer::Renderer()
		{
			if (gRenderer != nullptr)
				Utilities::ErrorUtils::ThrowException(L"Initialization failed. Please restart Geometry Dash and try again!");

			ImGui::CreateContext();
			SetTheme();

			Hooks::createHook(GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers"), wglSwapBuffers);
			Hook::applyQueuedActions();

			printf("Initialized Renderer\n");
		};

		Renderer::~Renderer()
		{
			printf("Deconstructed Renderer\n");
		};
	}
}