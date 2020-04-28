#pragma once
#include "ImpPCH.h"
#include "../Core.h"

namespace Imp
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Categories will help us sort the events in groups that allows us to only notify the observers that want events from a certain category
	// for example: The Input manager manager only wants to get events that are initiated by the actions of the user (like a mouse click)
	// an event can have multiple flags enabled, this allows for a more specific distribution inside the input manager for example
	enum class EventCategory
	{
		None			= 0,
		Input			= 1 << 0,
		Mouse			= 1 << 1,
		Keyboard		= 1 << 2,
		MouseButton		= 1 << 3,
		Window			= 1 << 4
	};

	class IMP_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		
		inline bool IsInCategory(int category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_IsHandeled = false;
	};

	// This class basically checks if the incoming event equals the templated typename
	// If so, we call the callback function that was added to the Dispatch function
	// the returning bool will set the isHandeled variable to true or false depending on the logic
	// in the callback function
	// This pattern is also used in unreal engine
	class IMP_API EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			: m_Event(e)
		{ }

		~EventDispatcher() = default;

		template<typename T>
		bool Dispatch(std::function<bool(T&)> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_IsHandeled = func(*(T*)&m_Event);

				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};
}