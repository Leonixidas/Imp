#include <ImpPCH.h>
#include "Window.h"

#ifdef IMP_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Imp
{
	Ref<Window> Window::Create(const WindowProps& props)
	{
#ifdef IMP_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		IMP_CORE_ASSERT(false, "Unknown platform");
		return nullptr;
#endif
	}

}