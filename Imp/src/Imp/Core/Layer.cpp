#include "ImpPCH.h"
#include "Layer.h"

Imp::Layer::Layer(std::string name)
	: m_LayerName(std::move(name))
{
}
