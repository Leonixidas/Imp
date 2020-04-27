#include "ImpPCH.h"
#include "Log.h"

//TODO improve the logging system
namespace Imp
{
	tm* Log::m_pTime = new tm();

	void Log::Info(const std::string& message)
	{
		CalculateTime();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::INFO));
		PrintTime();
		std::cout << "INFO " <<  message << std::endl;
	}

	void Log::Warn(const std::string& message)
	{
		CalculateTime();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::WARN));
		PrintTime();
		std::cout << "WARNING " << message << std::endl;
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

	void Log::CalculateTime()
	{
		time_t t = time(0);

		localtime_s(m_pTime, &t);
	}
	void Log::PrintTime()
	{
		std::cout << '[' << std::setw(2) << std::setfill('0') << m_pTime->tm_hour << ':' 
			<< std::setw(2) << std::setfill('0') << m_pTime->tm_min << ':' 
			<< std::setw(2) << std::setfill('0') << m_pTime->tm_sec << "] ";
	}
}
