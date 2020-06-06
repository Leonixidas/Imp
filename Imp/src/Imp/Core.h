#pragma once
#define BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef IMP_WINDOWS
#endif

#ifdef IMP_ENABLE_ASSERTS
	#define IMP_ASSERT( x, ...) if(!x) {IMP_ERROR(__VA_ARGS__); __debugbreak;}
#else
	#define IMP_ASSERT(x,...)
#endif