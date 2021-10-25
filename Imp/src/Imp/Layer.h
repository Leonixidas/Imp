#pragma once
#include "Events/Event.h"

namespace Imp
{
class Layer
{
public:
	explicit Layer(std::string const& name);

	virtual ~Layer() = default;

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void Update();
	virtual void Render();
	virtual void OnImGuiRender() ;
	virtual void OnEvent(Event& e);
	virtual void OnEnabled() {}

	void SetEnabled(bool const enabled);
	bool GetEnabled() const { return m_IsEnabled; }

	std::string const& GetName() const { return m_LayerName; }

protected:
	std::string m_LayerName;
	bool m_IsEnabled = true;
};
}

