#pragma once
#include "Event.h"

namespace Imp
{
	class IMP_API KeyEvent : public Event
	{
	public:
		virtual int GetCategoryFlags() { return int(EventCategory::Input) & int(EventCategory::Keyboard); }
		int GetKeyCode() { return m_KeyCode; }

	protected:
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode)
		{ }

		int m_KeyCode = 0;
	};


	class IMP_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, bool repeated)
			: KeyEvent(keyCode)
			, m_Repeated(repeated)
		{ }

		bool GetIsRepeated() { return m_Repeated; }

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() { return GetStaticType(); }

	private:
		bool m_Repeated = false;
	};

	class IMP_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode)
		{
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() { return GetStaticType(); }
	};
}