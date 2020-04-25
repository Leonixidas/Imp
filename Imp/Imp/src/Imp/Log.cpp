#include "Log.h"
#include <Windows.h>
#include <iostream>


namespace Imp
{
	Log::Log()
	{
	}

	void Log::Info(const std::string& message)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::INFO));
		std::cout << message << std::endl;
	}

	void Log::Warn(const std::string& message)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::WARN));
		std::cout << message << std::endl;
	}

	void Log::Error(const std::string& message)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::FATAL));
		std::cout << message << std::endl;
	}

	void Log::StartFileLogging(const std::string& fileName)
	{
	}

	void Log::EndFileLogging()
	{
	}


}
