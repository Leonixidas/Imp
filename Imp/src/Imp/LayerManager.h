#pragma once
#include "Core.h"
#include "Layer.h"

namespace Imp
{
class LayerManager final
{
public:
	LayerManager();
	~LayerManager();

	void PushLayer(Ref<Layer> const& layer);
	void PopLayer(Ref<Layer> const& layer);
	void PushOverlay(Ref<Layer> const& overlay);
	void PopOverlay(Ref<Layer> const& overlay);

	std::vector<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }
	std::vector<Ref<Layer>>::iterator end() { return m_Layers.end(); }
	std::vector<Ref<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
	std::vector<Ref<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

private:
	std::vector<Ref<Layer>> m_Layers;
	int m_LayerInsert = 0;
};
}

