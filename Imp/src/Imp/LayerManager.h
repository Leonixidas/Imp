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

		void PushLayer(const Ref<Layer>& layer);
		void PopLayer(const Ref<Layer>& layer);
		void PushOverlay(const Ref<Layer>& overlay);
		void PopOverlay(const Ref<Layer>& overlay);

		std::vector<Ref<Layer>>::iterator begin() { return mLayers.begin(); }
		std::vector<Ref<Layer>>::iterator end() { return mLayers.end(); }
		std::vector<Ref<Layer>>::reverse_iterator rbegin() { return mLayers.rbegin(); }
		std::vector<Ref<Layer>>::reverse_iterator rend() { return mLayers.rend(); }

	private:
		std::vector<Ref<Layer>> mLayers;
		unsigned int mLayerInsert = 0;
	};
}

