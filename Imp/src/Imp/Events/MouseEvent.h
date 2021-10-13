#pragma once
#include "Event.h"

namespace Imp
{
//TODO change position variables when implementing the math library
class MouseButtonEvent : public Event
{
public:
	int GetMouseButton() const { return m_MouseButton; }

	virtual int GetCategoryFlags() const override { return static_cast<int>(EventCategory::MouseButton) & static_cast<int>(EventCategory::Input); }

protected:
	MouseButtonEvent(int const mouseButton)
		: m_MouseButton(mouseButton)
	{}
	int m_MouseButton;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int const mouseButton, bool const repeated)
		: MouseButtonEvent(mouseButton)
		, m_IsRepeated(repeated)
	{ }

	bool GetisRepeated() const { return m_IsRepeated; }


	static EventType GetStaticType() { return EventType::MouseButtonPressed; }
	virtual EventType GetEventType() const override { return GetStaticType(); }

	virtual std::string DebugInfo() const override
	{
		return "MouseButtonReleasedEvent: Mouse button " + std::to_string(m_MouseButton) + " got pressed.";
	}

private:
	bool m_IsRepeated = false;
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int const mouseButton)
		: MouseButtonEvent(mouseButton)
	{ }

	static EventType GetStaticType() { return EventType::MouseButtonReleased; }
	virtual EventType GetEventType() const override { return GetStaticType(); }

	virtual std::string DebugInfo() const override
	{
		return "MouseButtonReleasedEvent: Mouse button " + std::to_string(m_MouseButton) + " got released.";
	}
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float const xpos, float const ypos)
		: m_xPos(xpos)
		, m_yPos(ypos)
	{}

	virtual int GetCategoryFlags() const override { return static_cast<int>(EventCategory::Mouse) & static_cast<int>(EventCategory::Input); }
	static EventType GetStaticType() { return EventType::MouseMoved; }
	virtual EventType GetEventType() const override { return GetStaticType(); }

	float GetX() { return m_xPos; }
	float GetY() { return m_yPos; }

	virtual std::string DebugInfo() const override
	{
		std::string debugInfo{};
		debugInfo = "MouseMovedEvent: mouse pos [" + std::to_string(m_xPos) + ',' + std::to_string(m_yPos) + "].";
		return debugInfo;
	}

private:
	float m_xPos, m_yPos;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float const xVel, float const yVel)
		: m_xVel(xVel)
		, m_yVel(yVel)
	{}

	float GetX() const { return m_xVel; }
	float GetY() const { return m_yVel; }

	virtual int GetCategoryFlags() const override { return static_cast<int>(EventCategory::Mouse) & static_cast<int>(EventCategory::Input); }
	static EventType GetStaticType() { return EventType::MouseScrolled; }
	virtual EventType GetEventType() const override { return GetStaticType(); }

	virtual std::string DebugInfo() const override
	{
		return "MouseScrolledEvent: scroll velocity = [" + std::to_string(m_xVel) + ',' + std::to_string(m_yVel) + ']';
	}

private:
	float m_xVel, m_yVel;
};
}