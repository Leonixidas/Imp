#pragma once
#include "ImpPCH.h"
#include "../../Libs/GLFW/include/GLFW/glfw3.h"

namespace Imp
{
enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMoved,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// Categories will help us sort the events in groups that allows us to only notify the observers that want events from a certain category
// for example: The Input manager manager only wants to get events that are initiated by the actions of the user (like a mouse click)
// an event can have multiple flags enabled, this allows for a more specific distribution inside the input manager for example
enum EventCategory
{
	None			= 0,
	EventCategoryApplication		= 1 << 0,
	EventCategoryInput			= 1 << 1,
	EventCategoryMouse			= 1 << 2,
	EventCategoryKeyboard		= 1 << 3,
	EventCategoryMouseButton		= 1 << 4
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual char const* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class Event
{
	friend class EventDispatcher;
public:
	Event() = default;
	virtual ~Event() = default;

	virtual EventType GetEventType() const = 0;
	virtual char const* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(int const category)
	{
		return GetCategoryFlags() & category;
	}

	bool IsHandled() { return m_IsHandled; }

protected:
	bool m_IsHandled = false;
};

// This class basically checks if the incoming event equals the templated typename
// If so, we call the callback function that was added to the Dispatch function
// the returning bool will set the isHandeled variable to true or false depending on the logic
// in the callback function
// This pattern is also used in unreal engine
class EventDispatcher
{
public:
	EventDispatcher(Event& e)
		: m_Event(e)
	{ }

	~EventDispatcher() = default;

	template<typename T>
	bool Dispatch(std::function<bool(T&)> const& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_IsHandled = func(*reinterpret_cast<T*>(&m_Event));

			return true;
		}

		return false;
	}

private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, Event const& e)
{
	return os << e.ToString();
}
}