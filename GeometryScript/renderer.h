#pragma once

#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_win32.h"
#include <vector>
#include "window.h"
#include <stdio.h>

template<typename Base, typename T>
inline bool instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}

namespace GeometryScript::UI
{
	class Renderer
	{
	public:
		// GD Window
		HWND hWnd = 0;
		WNDPROC origWndProcFunc = 0;

		// ImGui Window Properties
		std::vector<Window::UIWindow*> uiWindows;

		Renderer();
		~Renderer();

		template<class T>
		inline bool HasWindowOfType()
		{
			return std::find_if(uiWindows.begin(), uiWindows.end(), [](auto* w) {
				printf("Instanceof: %s\n", instanceof<Window::UIWindow>(w) ? "true" : "false");
				return instanceof<T>(w);
			}) != std::end(uiWindows);
		}

		void SetTheme();
	};
}

extern GeometryScript::UI::Renderer* gRenderer;