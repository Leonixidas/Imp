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
			: m_XSize(x)
			, m_YSize(y)
		{ }

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType()const override { return GetStaticType(); }
		virtual int GetCategoryFlags() const override { return int(EventCategory::Window); }

		inline float GetX() { return m_XSize; }
		inline float GetY() { return m_YSize; }

		virtual const std::string DebugInfo() const override
		{
			return "WindowResizeEvent: new window size [" + std::to_string(m_XSize) + ',' + std::to_string(m_YSize) + "].";
		}

	private:
		float m_XSize, m_YSize;
	};
}