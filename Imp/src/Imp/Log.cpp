#include "ImpPCH.h"
#include "Log.h"

//TODO improve the logging system
namespace Imp
{
	tm* Log::mpTime = new tm();

	void Log::Info(const std::string& message)
	{
		CalculateTime();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::INFO));
		PrintTime();
		std::cout << "INFO: " << message << std::endl;
	}

	void Log::Succeed(const std::string& message)
	{
		CalculateTime();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::SUCCEED));
		PrintTime();
		std::cout << "SUCCEEDED: " <<  message << std::endl;
	}

	void Log::Warn(const std::string& message)
	{
		CalculateTime();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::WARN));
		PrintTime();
		std::cout << "WARNING: " << message << std::endl;
	}

	void Log::Error(const std::string& message)
	{
		CalculateTime();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::FATAL));
		PrintTime();
		std::cout << "ERROR: " << message << std::endl;
	}

	void Log::StartFileLogging(const std::string& fileName)
	{
	}

	void Log::EndFileLogging()
	{
	}

	void Log::CleanUp()
	{
		delete mpTime;
	}

	void Log::CalculateTime()
	{
		time_t t = time(0);

		localtime_s(mpTime, &t);
	}
	void Log::PrintTime()
	{
		std::cout << '[' << std::setw(2) << std::setfill('0') << mpTime->tm_hour << ':' 
			<< std::setw(2) << std::setfill('0') << mpTime->tm_min << ':' 
			<< std::setw(2) << std::setfill('0') << mpTime->tm_sec << "] ";
	}
}
