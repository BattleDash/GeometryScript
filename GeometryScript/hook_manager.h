#pragma once

#include <vector>
#include "hook.h"
#include <Windows.h>
#include <thread>
#include <mutex>

namespace GeometryScript::Hooks
{
	void createHook(Hook::address target, LPVOID replacement);
	Hook::address call(Hook::address replacement, Hook::address target);
	template <typename T>
	inline T call(T replacement, Hook::address target = nullptr)
	{
		return reinterpret_cast<T>(call(reinterpret_cast<Hook::address>(replacement), target));
	}
}