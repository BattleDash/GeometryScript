#include "program.h"
#include "error_utils.h"

#include <Windows.h>
#include <iostream>
#include <cstdio>
#include "MinHook/MinHook.h"
#include "geometrydash.h"
#include <filesystem>
#include "log_macros.h"

#pragma comment(lib, "OpenGL32.lib")

static inline std::filesystem::path get_module_path(HMODULE module)
{
	WCHAR buf[4096];
	return GetModuleFileNameW(module, buf, ARRAYSIZE(buf)) ? buf : std::filesystem::path();
}

GeometryScript::Program* gProgram;

namespace GeometryScript
{
	Program::Program(HMODULE module)
	{
		if (gProgram != nullptr || MH_Initialize() != MH_OK)
			Utilities::ErrorUtils::ThrowException(L"Initialization failed. Please restart Geometry Dash and try again!");

		std::filesystem::path geometryScriptDllPath = get_module_path(module);
		std::filesystem::path executablePath = get_module_path(nullptr);

		GeometryScript::Log::openLogFile(geometryScriptDllPath.filename().replace_extension(L".log"));

		LOG(INFO) << "Log loaded.";

		std::cout << "Welcome to Geometry Script!" << std::endl;

		gGeometryDash = new GeometryScript::GeometryDash;
	}

	Program::~Program()
	{
		std::cout << "Disposing!" << std::endl;
	}
}