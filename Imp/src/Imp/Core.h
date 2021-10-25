#pragma once
#include <memory>
#define BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef IMP_WINDOWS
#endif

#ifdef IMP_ENABLE_ASSERTS
	#define IMP_ASSERT( x, ...) if(!x) {IMP_CORE_FATAL(__VA_ARGS__); __debugbreak;}
#else
	#define IMP_ASSERT(x,...)
#endif

namespace Imp
{
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T>
using Weak = std::weak_ptr<T>;
}