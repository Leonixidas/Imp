#pragma once
#include "Event.h"

namespace Imp
{

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}
		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual int GetCategoryFlags() const override { return int(EventCategory::Window); }

		virtual const std::string DebugInfo() const override
		{
			return "WindowCloseEvent: Window is being closed.";
		}
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(float x, float y)
			: mXSize(x)
			, mYSize(y)
		{ }

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType()const override { return GetStaticType(); }
		virtual int GetCategoryFlags() const override { return int(EventCategory::Window); }

		inline float GetX() { return mXSize; }
		inline float GetY() { return mYSize; }

		virtual const std::string DebugInfo() const override
		{
			return "WindowResizeEvent: new window size [" + std::to_string(mXSize) + ',' + std::to_string(mYSize) + "].";
		}

	private:
		float mXSize, mYSize;
	};
}