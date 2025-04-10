#pragma once
#include "ImpPCH.h"
#include "Base.h"
#include "Imp/Events/Event.h"

namespace Imp
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(std::string title = "Imp Engine", uint32_t const width = 1600, uint32_t const height = 900)
			: Title(std::move(title))
			, Width(width)
			, Height(height)
		{ }
	};

	class Window
	{
	public:
		using EventCallBack = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallBack(const EventCallBack& callback) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool vsync) = 0;

		virtual void* GetNativeWindow() const = 0;

		static Ref<Window> Create(const WindowProps& props = WindowProps());
	};
}
