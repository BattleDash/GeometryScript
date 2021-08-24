#pragma once

#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

namespace ImGui
{
	static void Header(const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[2];

		ImGui::PushFont(headerFont);
		ImGui::Text(text);
		ImGui::PopFont();
	}

	static void Header(ImVec4 color, const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[2];

		ImGui::PushFont(headerFont);
		ImGui::TextColored(color, text);
		ImGui::PopFont();
	}

	static void Header2(const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[3];

		ImGui::PushFont(headerFont);
		ImGui::Text(text);
		ImGui::PopFont();
	}

	static void Header2(ImVec4 color, const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[3];

		ImGui::PushFont(headerFont);
		ImGui::TextColored(color, text);
		ImGui::PopFont();
	}

	static void SmallText(const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[1];

		ImGui::PushFont(headerFont);
		ImGui::Text(text);
		ImGui::PopFont();
	}

	static void SmallText(ImVec4 color, const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[1];

		ImGui::PushFont(headerFont);
		ImGui::TextColored(color, text);
		ImGui::PopFont();
	}

	static void BoldText(const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[4];

		ImGui::PushFont(headerFont);
		ImGui::Text(text);
		ImGui::PopFont();
	}

	static void BoldText(ImVec4 color, const char* text)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImFont* headerFont = atlas->Fonts[4];

		ImGui::PushFont(headerFont);
		ImGui::TextColored(color, text);
		ImGui::PopFont();
	}
}