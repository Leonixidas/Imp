#pragma once
#include "Imp/Core/Base.h"
#include "Imp/Core/Log.h"
#include <filesystem>

#ifdef IMP_ENABLE_ASSERTS

// Alternatively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define IMP_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { IMP##type##ERROR(msg, __VA_ARGS__); IMP_DEBUG_BREAK(); } }
#define IMP_INTERNAL_ASSERT_WITH_MSG(type, check, ...) IMP_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define IMP_INTERNAL_ASSERT_NO_MSG(type, check) IMP_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", IMP_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define IMP_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define IMP_INTERNAL_ASSERT_GET_MACRO(...) IMP_EXPAND_MACRO( IMP_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, IMP_INTERNAL_ASSERT_WITH_MSG, IMP_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define IMP_ASSERT(...) IMP_EXPAND_MACRO( IMP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define IMP_CORE_ASSERT(...) IMP_EXPAND_MACRO( IMP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define IMP_ASSERT(...)
#define IMP_CORE_ASSERT(...)
#endif