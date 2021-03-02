#include "pch.h"
#include "LayerList.h"

namespace pawn {

	LayerList::LayerList() {
		m_LayerInsert = m_Layers.begin();
	}

	void LayerList::Clear() {
		m_LayerInsert = m_Layers.begin();
		m_Layers.clear();
	}

	bool LayerList::PopLayer(const std::shared_ptr<Layer>& layer) {
		std::vector<std::shared_ptr<Layer>>::iterator result = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (result != m_Layers.end()) {
			m_Layers.erase(result);
			--m_LayerInsert;
			return true;
		}

		return false;
	}
	
	void LayerList::PushLayer(const std::shared_ptr<Layer>& layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	bool LayerList::PopOverlay(const std::shared_ptr<Layer>& overlay) {
		std::vector<std::shared_ptr<Layer>>::iterator result = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (result != m_Layers.end()) {
			m_Layers.erase(result);
			return true;
		}

		return false;
	}
	
	void LayerList::PushOverlay(const std::shared_ptr<Layer>& overlay) {
		m_Layers.emplace_back(overlay);
	}

}