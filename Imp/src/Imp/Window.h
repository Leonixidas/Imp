#pragma once
#include "ImpPCH.h"
#include "Core.h"

namespace Imp
{
	struct WindowProps
	{
		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;

		WindowProps()
			: m_Title("Imp Engine")
			, m_Width(1280)
			, m_Height(720)
		{ }
	};

	class IMP_API Window
	{
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool vsync) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}