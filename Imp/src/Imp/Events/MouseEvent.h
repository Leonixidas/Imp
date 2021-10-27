#pragma once
#include "Event.h"
#include <sstream>
#include "Imp/MouseCodes.h"

namespace Imp
{
class MouseButtonEvent : public Event
{
public:
	int GetMouseButton() const { return m_MouseButton; }

	EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput | EventCategoryMouse)

protected:
	MouseButtonEvent(MouseCode const mouseButton)
		: m_MouseButton(mouseButton)
	{}

	MouseCode m_MouseButton;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(MouseCode const mouseButton, bool const repeated)
		: MouseButtonEvent(mouseButton)
		, m_IsRepeated(repeated)
	{ }

	bool GetisRepeated() const { return m_IsRepeated; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_MouseButton;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed)

private:
	bool m_IsRepeated = false;
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(MouseCode const mouseButton)
		: MouseButtonEvent(mouseButton)
	{ }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_MouseButton;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float const xpos, float const ypos)
		: m_xPos(xpos)
		, m_yPos(ypos)
	{}

	float GetX() const { return m_xPos; }
	float GetY() const { return m_yPos; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << "x=" << GetX() << " y=" << GetY();
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

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

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << "x=" << GetX() << " y=" << GetY();
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
	float m_xVel, m_yVel;
};
}