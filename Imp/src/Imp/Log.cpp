#include "ImpPCH.h"
#include "Log.h"

//TODO improve the logging system
namespace Imp
{
tm* Log::m_pTime = new tm();

void Log::Info(std::string const& message)
{
	CalculateTime();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::INFO));
	PrintTime();
	std::cout << "INFO: " << message << std::endl;
}

void Log::Succeed(std::string const& message)
{
	CalculateTime();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::SUCCEED));
	PrintTime();
	std::cout << "SUCCEEDED: " <<  message << std::endl;
}

void Log::Warn(std::string const& message)
{
	CalculateTime();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::WARN));
	PrintTime();
	std::cout << "WARNING: " << message << std::endl;
}

void Log::Error(std::string const& message)
{
	CalculateTime();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(Level::FATAL));
	PrintTime();
	std::cout << "ERROR: " << message << std::endl;
}

void Log::StartFileLogging(std::string const& fileName)
{
}

void Log::EndFileLogging()
{
}

void Log::CleanUp()
{
	delete m_pTime;
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
