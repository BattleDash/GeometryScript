#pragma once

#include <stdio.h>
#include <vector>
#include "MinHook/MinHook.h"
#include "error_utils.h"
#include "platform_utils.h"
#include <iostream>
#include <fstream>
#include "comdef.h"
#include <string>
#include <thread>
#include <mutex>
#include <deque>
#include <sstream>
#include "renderer.h"

namespace GeometryScript
{
	class GeometryDash
	{
	public:
		GeometryDash();
		~GeometryDash();
	};
}

static GeometryScript::GeometryDash* gGeometryDash;