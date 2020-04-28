#pragma once
#include "Core.h"
#include <string>

namespace Imp
{
	enum class Level
	{
		INFO = 0x0007,
		SUCCEED = 0x0002,
		WARN = 0x0006,
		FATAL = 0x0004
	};

	class IMP_API Log
	{
	public:
		static void Info(const std::string& message);
		static void Succeed(const std::string& message);
		static void Warn(const std::string& message);
		static void Error(const std::string& message);

		static void StartFileLogging(const std::string& fileName);
		static void EndFileLogging();

		static void CleanUp();

	private:
		static void CalculateTime();
		static void PrintTime();
		static tm* m_pTime;
	};
}

