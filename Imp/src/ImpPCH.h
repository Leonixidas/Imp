#pragma once
#include "Imp/Core/PlatformDetection.h"

#ifdef HZ_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <vld.h>
#include <iostream>
#include <iomanip>
#include <functional>
#include <memory>
#include <algorithm>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>

#include "Imp/Core/Base.h"
#include "Imp/Core/Log.h"
#include "Imp/Debug/Instrumentor.h"

#ifdef IMP_PLATFORM_WINDOWS
	#include <Windows.h>
#endif