#pragma once
#include "Core.h"
#include <string>
#include "spdlog/spdlog.h"

namespace Imp
{
class Log
{
public:
	static void Init();

	inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
	static Ref<spdlog::logger> s_CoreLogger;
	static Ref<spdlog::logger> s_ClientLogger;
};
}

//Core log macros
#define IMP_CORE_ERROR(...)	::Imp::Log::GetCoreLogger()->error(__VA_ARGS__)
#define IMP_CORE_WARN(...)	::Imp::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define IMP_CORE_INFO(...)	::Imp::Log::GetCoreLogger()->info(__VA_ARGS__)
#define IMP_CORE_TRACE(...) ::Imp::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define IMP_CORE_FATAL(...) ::Imp::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define IMP_ERROR(...)		::Imp::Log::GetClientLogger()->error(__VA_ARGS__)
#define IMP_WARN(...)		::Imp::Log::GetClientLogger()->warn(__VA_ARGS__)
#define IMP_INFO(...)		::Imp::Log::GetClientLogger()->info(__VA_ARGS__)
#define IMP_TRACE(...)		::Imp::Log::GetClientLogger()->trace(__VA_ARGS__)
#define IMP_FATAL(...)		::Imp::Log::GetClientLogger()->critical(__VA_ARGS__)