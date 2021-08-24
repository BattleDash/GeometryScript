#pragma once

#include <Windows.h>

namespace GeometryScript
{
	namespace Utilities
	{
		//!  Utilities for Error handling.
		class ErrorUtils
		{
		public:
			static void ThrowException(LPCWSTR message); //!< ThrowException pauses execution and prompts the user to restart the game.
		};
	}
}