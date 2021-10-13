#include "ImpPCH.h"
#include "Layer.h"

Imp::Layer::Layer(std::string const& name)
	: m_LayerName(name)
{
}

void Imp::Layer::SetEnabled(bool const enabled)
{
	m_IsEnabled = enabled;
	if (enabled)
	{
		OnEnabled();
	}
}