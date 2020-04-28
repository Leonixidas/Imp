#pragma once
#include "Event.h"

namespace Imp
{

	class IMP_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}
		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual int GetCategoryFlags() const override { return int(EventCategory::Window); }
	};

	class IMP_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(float x, float y)
			: m_XSize(x)
			, m_YSize(y)
		{ }

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType()const override { return GetStaticType(); }
		virtual int GetCategoryFlags() const override { return int(EventCategory::Window); }

	private:
		float m_XSize, m_YSize;
	};
}