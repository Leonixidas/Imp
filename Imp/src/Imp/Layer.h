#pragma once
#include "Events/Event.h"

namespace Imp
{
class Layer
{
public:
	explicit Layer(std::string const& name);

	virtual ~Layer() = default;

	virtual void OnAttach() = 0;
	virtual void OnDetach() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnImGuiRender() = 0;
	virtual void OnEvent(Event& e) = 0;
	virtual void OnEnabled() = 0;

	void SetEnabled(bool const enabled);
	bool GetEnabled() const { return m_IsEnabled; }

	std::string const& GetName() const { return m_LayerName; }

protected:
	std::string m_LayerName;
	bool m_IsEnabled = true;
};
}

