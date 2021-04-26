#pragma once
#include "Core.h"
#include "Events/Event.h"
#include <string>

namespace Imp
{
	class Layer
	{
	public:
		explicit Layer(const std::string& name);

		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void Update();
		virtual void Render();
		virtual void OnImGuiRender();
		virtual void OnEvent(Event& e);
		virtual void OnEnabled() {}

		void SetEnabled(bool enabled);
		inline bool GetEnabled() const { return m_IsEnabled; }

		inline const std::string& GetName() const { return m_LayerName; }

	protected:
		std::string m_LayerName;
		bool m_IsEnabled = true;
	};
}

