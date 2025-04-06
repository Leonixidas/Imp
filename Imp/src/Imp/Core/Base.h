#pragma once
#include "Imp/Core/PlatformDetection.h"
#include <memory>
#ifdef IMP_DEBUG
#if defined(IMP_PLATFORM_WINDOWS)
#define IMP_DEBUG_BREAK() __debugbreak()
#elif defined(IMP_PLATFORM_LINUX)
#include <signal.h>
#define HZ_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define IMP_ENABLE_ASSERTS
#else
#define HZ_DEBUGBREAK()
#endif

#define IMP_EXPAND_MACRO(x) x
#define IMP_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define IMP_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Imp
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}


#include "Imp/Core/Log.h"
#include "Imp/Core/Assert.h"