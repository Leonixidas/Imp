#pragma once
#include "Event.h"

namespace Imp
{
	//TODO change position variables when implementing the math library
	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return m_MouseButton; }

		virtual int GetCategoryFlags() const override { return int(EventCategory::MouseButton) & int(EventCategory::Input); }

	protected:
		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton)
		{}
		int m_MouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseButton, bool repeated)
			: MouseButtonEvent(mouseButton)
			, m_IsRepeated(repeated)
		{ }

		bool GetisRepeated() const { return m_IsRepeated; }

		
		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			return "MouseButtonReleasedEvent: Mouse button " + std::to_string(m_MouseButton) + " got pressed.";
		}

	private:
		bool m_IsRepeated = false;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton)
		{ }

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			return "MouseButtonReleasedEvent: Mouse button " + std::to_string(m_MouseButton) + " got released.";
		}
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int xvel, int yvel)
			: m_xVel(xvel)
			, m_yVel(yvel)
		{}

		virtual int GetCategoryFlags() const override { return int(EventCategory::Mouse) & int(EventCategory::Input); }
		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			std::string debugInfo{};
			debugInfo = "MouseMovedEvent: mouse pos [" + std::to_string(m_xVel) + ',' + std::to_string(m_yVel) + "].";
			return debugInfo;
		}

	private:
		int m_xVel, m_yVel;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float vel)
			: m_Vel(vel)
		{}

		float GetScrollVelocity() const { return m_Vel; }

		virtual int GetCategoryFlags() const override { return int(EventCategory::Mouse) & int(EventCategory::Input); }
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			return "MouseScrolledEvent: scroll velocity = " + std::to_string(m_Vel);
		}

	private:
		float m_Vel;
	};
}