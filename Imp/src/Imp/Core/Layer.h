#pragma once
#include "Timestep.h"
#include "Imp/Events/Event.h"

namespace Imp
{
	class Layer
	{
	public:
		explicit Layer(std::string name = "Layer");

		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void Render() {}
		virtual void OnImGuiRender() {} 
		virtual void OnEvent(Event& e) {}

		std::string const& GetName() const { return m_LayerName; }

	protected:
		std::string m_LayerName;
	};
}

