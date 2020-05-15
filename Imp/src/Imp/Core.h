#pragma once

#define BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef IMP_WINDOWS
#endif