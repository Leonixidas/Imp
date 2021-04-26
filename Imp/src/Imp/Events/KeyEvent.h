#pragma once
#include "Event.h"

namespace Imp
{
	class KeyEvent : public Event
	{
	public:
		virtual int GetCategoryFlags() const override { return int(EventCategory::Input) & int(EventCategory::Keyboard); }
		inline int GetKeyCode() { return mKeyCode; }

	protected:
		KeyEvent(int keyCode)
			: mKeyCode(keyCode)
		{ }

		int mKeyCode = 0;
	};


	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, bool repeated)
			: KeyEvent(keyCode)
			, mRepeated(repeated)
		{ }

		bool GetIsRepeated() { return mRepeated; }

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			int scanCode = glfwGetKeyScancode(mKeyCode);
			const char* name = glfwGetKeyName(mKeyCode, scanCode);
			if (name != nullptr)
			{
				if (!mRepeated)
					return "KeyPressedEvent: '" + std::string(name) + "' got pressed";
				else
					return "KeyPressedEvent: '" + std::string(name) + "' got pressed as a repeat";
			}
			else
				return "";

		}

	private:
		bool mRepeated = false;
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
			int scanCode = glfwGetKeyScancode(mKeyCode);
			const char* name = glfwGetKeyName(mKeyCode, scanCode);
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
			int scanCode = glfwGetKeyScancode(mKeyCode);
			const char* name = glfwGetKeyName(mKeyCode, scanCode);
			if (name != nullptr)
				return "KeyTypedEvent: '" + std::string(name) + "'";
			else
				return "";
		}
	};
}