#include "ImpPCH.h"
#include "LayerManager.h"
#include "Log.h"

Imp::LayerManager::LayerManager()
	: m_Layers()
{
	m_LayerInsert = m_Layers.begin();
}

Imp::LayerManager::~LayerManager()
{
	for (Layer* l : m_Layers)
	{
		delete l;
		l = nullptr;
	}

	m_Layers.clear();
}

void Imp::LayerManager::PushLayer(Layer* layer)
{
	auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);

	if (iter == m_Layers.end())
	{
		m_Layers.emplace(m_LayerInsert, layer);
		layer->OnAttach();
	}
	else
	{
		Log::Warn("Layer already pushed on the stack: " + layer->GetName());
	}
}

void Imp::LayerManager::PopLayer(Layer* layer)
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

void Imp::LayerManager::PushOverlay(Layer* overlay)
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

void Imp::LayerManager::PopOverlay(Layer* overlay)
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
