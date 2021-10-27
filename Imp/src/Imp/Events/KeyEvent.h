#pragma once
#include "Event.h"
#include <sstream>
#include "Imp/KeyCodes.h"

namespace Imp
{
class KeyEvent : public Event
{
public:
	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	inline KeyCode GetKeyCode() { return m_KeyCode; }

protected:
	KeyEvent(KeyCode const keyCode)
		: m_KeyCode(keyCode)
	{ }

	KeyCode m_KeyCode = 0;
};


class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(KeyCode const keyCode, uint16_t const repeated)
		: KeyEvent(keyCode)
		, m_RepeatCount(repeated)
	{ }

	uint16_t GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed)

private:
	uint16_t m_RepeatCount = false;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(KeyCode const keyCode)
		: KeyEvent(keyCode)
	{
	}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(KeyCode const keyCode)
		: KeyEvent(keyCode)
	{
	}

	EVENT_CLASS_TYPE(KeyTyped)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}
};
}