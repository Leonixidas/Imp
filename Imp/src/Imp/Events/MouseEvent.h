#pragma once
#include "Event.h"

namespace Imp
{
	//TODO change position variables when implementing the math library
	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return mMouseButton; }

		virtual int GetCategoryFlags() const override { return int(EventCategory::MouseButton) & int(EventCategory::Input); }

	protected:
		MouseButtonEvent(int mouseButton)
			: mMouseButton(mouseButton)
		{}
		int mMouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseButton, bool repeated)
			: MouseButtonEvent(mouseButton)
			, mIsRepeated(repeated)
		{ }

		bool GetisRepeated() const { return mIsRepeated; }

		
		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			return "MouseButtonReleasedEvent: Mouse button " + std::to_string(mMouseButton) + " got pressed.";
		}

	private:
		bool mIsRepeated = false;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton)
		{ }

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			return "MouseButtonReleasedEvent: Mouse button " + std::to_string(mMouseButton) + " got released.";
		}
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float xpos, float ypos)
			: mxPos(xpos)
			, myPos(ypos)
		{}

		virtual int GetCategoryFlags() const override { return int(EventCategory::Mouse) & int(EventCategory::Input); }
		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		float GetX() { return mxPos; }
		float GetY() { return myPos; }

		virtual const std::string DebugInfo() const override
		{
			std::string debugInfo{};
			debugInfo = "MouseMovedEvent: mouse pos [" + std::to_string(mxPos) + ',' + std::to_string(myPos) + "].";
			return debugInfo;
		}

	private:
		float mxPos, myPos;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xvel, float yvel)
			: mxVel(xvel)
			, myVel(yvel)
		{}

		float GetX() const { return mxVel; }
		float GetY() const { return myVel; }

		virtual int GetCategoryFlags() const override { return int(EventCategory::Mouse) & int(EventCategory::Input); }
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		virtual const std::string DebugInfo() const override
		{
			return "MouseScrolledEvent: scroll velocity = [" + std::to_string(mxVel) + ',' + std::to_string(myVel) + ']';
		}

	private:
		float mxVel, myVel;
	};
}