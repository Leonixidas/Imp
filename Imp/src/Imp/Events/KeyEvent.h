#pragma once
#include "Event.h"

namespace Imp
{
	class KeyEvent : public Event
	{
	public:
		virtual int GetCategoryFlags() const override { return int(EventCategory::Input) & int(EventCategory::Keyboard); }
		inline int GetKeyCode() { return m_KeyCode; }

	protected:
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode)
		{ }

		int m_KeyCode = 0;
	};


	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, bool repeated)
			: KeyEvent(keyCode)
			, m_Repeated(repeated)
		{ }

		bool GetIsRepeated() { return m_Repeated; }

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			int scanCode = glfwGetKeyScancode(m_KeyCode);
			const char* name = glfwGetKeyName(m_KeyCode, scanCode);
			if (name != nullptr)
			{
				if (!m_Repeated)
					return "KeyPressedEvent: '" + std::string(name) + "' got pressed";
				else
					return "KeyPressedEvent: '" + std::string(name) + "' got pressed as a repeat";
			}
			else
				return "";

		}

	private:
		bool m_Repeated = false;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode)
		{
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			int scanCode = glfwGetKeyScancode(m_KeyCode);
			const char* name = glfwGetKeyName(m_KeyCode, scanCode);
			if (name != nullptr)
				return "KeyReleasedEvent: '" + std::string(name) + "' got released";
			else
				return "";
		}
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode)
		{
		}

		static EventType GetStaticType() { return EventType::KeyTyped; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			int scanCode = glfwGetKeyScancode(m_KeyCode);
			const char* name = glfwGetKeyName(m_KeyCode, scanCode);
			if (name != nullptr)
				return "KeyTypedEvent: '" + std::string(name) + "'";
			else
				return "";
		}
	};
}