#pragma once
#include "Core.h"
#include "Layer.h"
#include <vector>

namespace Imp
{
	class LayerManager final
	{
	public:
		LayerManager();
		~LayerManager();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator Begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator End() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rBegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rEnd() { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}

