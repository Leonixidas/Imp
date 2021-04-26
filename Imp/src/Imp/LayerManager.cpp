#include "ImpPCH.h"
#include "LayerManager.h"
#include "Log.h"

Imp::LayerManager::LayerManager()
	: m_Layers()
{
}

Imp::LayerManager::~LayerManager()
{
	m_Layers.clear();
}

void Imp::LayerManager::PushLayer(const Ref<Layer>& layer)
{
	auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);

	if (iter == m_Layers.end())
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsert, layer);
		layer->OnAttach();
	}
	else
	{
		Log::Warn("Layer already pushed on the stack: " + layer->GetName());
	}
}

void Imp::LayerManager::PopLayer(const Ref<Layer>& layer)
{
	auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);

	if (iter != m_Layers.end())
	{
		m_Layers.erase(iter);
		--m_LayerInsert;

		layer->OnDetach();
	}
	else
	{
		Log::Warn("Layer is not in the stack: " + layer->GetName());
	}
}

void Imp::LayerManager::PushOverlay(const Ref<Layer>& overlay)
{
	auto iter = std::find(m_Layers.begin(), m_Layers.end(), overlay);

	if (iter == m_Layers.end())
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}
	else
	{
		Log::Warn("Layer already pushed on the stack: " + overlay->GetName());
	}
}

void Imp::LayerManager::PopOverlay(const Ref<Layer>& overlay)
{
	auto iter = std::find(m_Layers.begin(), m_Layers.end(), overlay);

	if (iter != m_Layers.end())
	{
		m_Layers.erase(iter);
		overlay->OnDetach();
	}
	else
	{
		Log::Warn("Layer is not in the stack: " + overlay->GetName());
	}
}
