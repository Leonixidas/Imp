#include "ImpPCH.h"
#include "LayerManager.h"
#include "Log.h"

Imp::LayerManager::LayerManager()
	: mLayers()
{
}

Imp::LayerManager::~LayerManager()
{
	mLayers.clear();
}

void Imp::LayerManager::PushLayer(const Ref<Layer>& layer)
{
	auto iter = std::find(mLayers.begin(), mLayers.end(), layer);

	if (iter == mLayers.end())
	{
		mLayers.emplace(mLayers.begin() + mLayerInsert, layer);
		layer->OnAttach();
	}
	else
	{
		Log::Warn("Layer already pushed on the stack: " + layer->GetName());
	}
}

void Imp::LayerManager::PopLayer(const Ref<Layer>& layer)
{
	auto iter = std::find(mLayers.begin(), mLayers.end(), layer);

	if (iter != mLayers.end())
	{
		mLayers.erase(iter);
		--mLayerInsert;

		layer->OnDetach();
	}
	else
	{
		Log::Warn("Layer is not in the stack: " + layer->GetName());
	}
}

void Imp::LayerManager::PushOverlay(const Ref<Layer>& overlay)
{
	auto iter = std::find(mLayers.begin(), mLayers.end(), overlay);

	if (iter == mLayers.end())
	{
		mLayers.emplace_back(overlay);
		overlay->OnAttach();
	}
	else
	{
		Log::Warn("Layer already pushed on the stack: " + overlay->GetName());
	}
}

void Imp::LayerManager::PopOverlay(const Ref<Layer>& overlay)
{
	auto iter = std::find(mLayers.begin(), mLayers.end(), overlay);

	if (iter != mLayers.end())
	{
		mLayers.erase(iter);
		overlay->OnDetach();
	}
	else
	{
		Log::Warn("Layer is not in the stack: " + overlay->GetName());
	}
}
