#include "ImpPCH.h"
#include "Layer.h"

Imp::Layer::Layer(const std::string& name)
	: m_LayerName(name)
{
}

Imp::Layer::~Layer()
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

void Imp::Layer::SetEnabled(bool enabled)
{
	m_IsEnabled = enabled;
	if (enabled)
		OnEnabled();
}