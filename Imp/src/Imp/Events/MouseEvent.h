#pragma once
#include "Event.h"

namespace Imp
{
	//TODO change position variables when implementing the math library
	class IMP_API MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return m_MouseButton; }

		virtual int GetCategoryFlags() { return int(EventCategory::MouseButton) & int(EventCategory::Input); }

	protected:
		MouseButtonEvent(int mouseButton, float xpos, float ypos)
			: m_MouseButton(mouseButton)
			, m_xPos(xpos)
			, m_yPos(ypos)
		{}

		float m_xPos, m_yPos;
		int m_MouseButton;
	};

	class IMP_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseButton, float xpos, float ypos, bool repeated)
			: MouseButtonEvent(mouseButton, xpos, ypos)
			, m_IsRepeated(repeated)
		{ }

		bool GetisRepeated() const { return m_IsRepeated; }

		
		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() { return GetStaticType(); }

	private:
		bool m_IsRepeated = false;
	};

	class IMP_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseButton, float xpos, float ypos)
			: MouseButtonEvent(mouseButton, xpos, ypos)
		{ }

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() { return GetStaticType(); }
	};

	class IMP_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float xvel, float yvel)
			: m_xVel(xvel)
			, m_yVel(yvel)
		{}

		virtual int GetCategoryFlags() { return int(EventCategory::Mouse) & int(EventCategory::Input); }
		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() { return GetStaticType(); }

	private:
		float m_xVel, m_yVel;
	};

	class IMP_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float vel)
			: m_Vel(vel)
		{}

		float GetScrollVelocity() const { return m_Vel; }

		virtual int GetCategoryFlags() { return int(EventCategory::Mouse) & int(EventCategory::Input); }
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() { return GetStaticType(); }

	private:
		float m_Vel;
	};
}