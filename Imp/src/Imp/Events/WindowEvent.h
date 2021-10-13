#pragma once
#include "Event.h"

namespace Imp
{

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;
	static EventType GetStaticType() { return EventType::WindowClose; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual int GetCategoryFlags() const override { return int(EventCategory::Window); }

	virtual std::string DebugInfo() const override
	{
		return "WindowCloseEvent: Window is being closed.";
	}
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(float const w, float const h)
		: m_Width(w)
		, m_Height(h)
	{ }

	static EventType GetStaticType() { return EventType::WindowResize; }
	virtual EventType GetEventType()const override { return GetStaticType(); }
	virtual int GetCategoryFlags() const override { return static_cast<int>(EventCategory::Window); }

	inline float GetWidth() const { return m_Width; }
	inline float GetHeight() const { return m_Height; }

	virtual std::string DebugInfo() const override
	{
		return "WindowResizeEvent: new window size [" + std::to_string(m_Width) + ',' + std::to_string(m_Height) + "].";
	}

private:
	float m_Width, m_Height;
};
}