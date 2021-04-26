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

		std::chrono::high_resolution_clock::time_point mPrev{};
		std::chrono::high_resolution_clock::time_point mNow{};

		unsigned int mFrames{};
		float mAccumTime{}, mElapsedTime{};


		void Update()
		{
			mNow = std::chrono::high_resolution_clock::now();
			mElapsedTime = std::chrono::duration<float>(mNow - mPrev).count();
			mAccumTime += mElapsedTime;
		}

		bool Initialize()
		{
			mPrev = std::chrono::high_resolution_clock::now();
			mNow = mPrev;

			++mFrames;

			return true;
		}

	public:

		float GetElapsed()
		{
			return mElapsedTime;
		}

		float GetFPS()
		{
			return mFrames / (float)mAccumTime;
		}

		float GetAverageTime()
		{
			return mAccumTime / mFrames;
		}
	};
}