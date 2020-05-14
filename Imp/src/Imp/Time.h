#pragma once
#include "Core.h"
#include "Singleton.h"
#include <chrono>

namespace Imp
{
	class Time : public Singleton<Time>
	{
	private:

		friend class Application;

		std::chrono::high_resolution_clock::time_point m_Prev{};
		std::chrono::high_resolution_clock::time_point m_Now{};

		unsigned int m_Frames{};
		float m_AccumTime{}, m_ElapsedTime{};


		void Update()
		{
			m_Now = std::chrono::high_resolution_clock::now();
			m_ElapsedTime = std::chrono::duration<float>(m_Now - m_Prev).count();
			m_AccumTime += m_ElapsedTime;
		}

		bool Initialize()
		{
			m_Prev = std::chrono::high_resolution_clock::now();
			m_Now = m_Prev;

			++m_Frames;
		}

	public:

		float GetElapsed()
		{
			return m_ElapsedTime;
		}

		int GetFPS()
		{
			return m_Frames / m_AccumTime;
		}

		float GetAverageTime()
		{
			return m_AccumTime / m_Frames;
		}
	};
}