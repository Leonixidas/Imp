#include "ImpPCH.h"
#include "Layer.h"

Imp::Layer::Layer(std::string const& name)
	: m_LayerName(name)
{
}

void Imp::Layer::OnAttach()
{
}

void Imp::Layer::OnDetach()
{
}

void Imp::Layer::Update()
{
}

void Imp::Layer::Render()
{
}

void Imp::Layer::OnImGuiRender()
{
}

void Imp::Layer::OnEvent(Event& e)
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
