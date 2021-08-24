#pragma once

#include <windows.h>

namespace GeometryScript
{
	class Program
	{
	public:
		Program(HMODULE module);
		~Program();
	};
}

extern GeometryScript::Program* gProgram;