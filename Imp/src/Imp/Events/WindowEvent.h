#pragma once
#include "Event.h"
#include <sstream>

namespace Imp
{

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;
	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int const w, int const h)
		: m_Width(w)
		, m_Height(h)
	{ }

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << GetName() << ": x=" << m_Width << " y=" << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)


private:
	int m_Width, m_Height;
};
}