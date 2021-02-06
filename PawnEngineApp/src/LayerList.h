#pragma once

namespace pawn {

	class Layer;
	
	class LayerList {
		
		public:
			LayerList();

			bool PopLayer(const std::shared_ptr<Layer>& layer);
			void PushLayer(const std::shared_ptr<Layer>& layer);

			bool PopOverlay(const std::shared_ptr<Layer>& overlay);
			void PushOverlay(const std::shared_ptr<Layer>& overlay);

			void Clear();

			const std::vector<std::shared_ptr<Layer>>& GetLayers() const { return m_Layers; }

			std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
			std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
	
		private:
			std::vector<std::shared_ptr<Layer>> m_Layers;
			std::vector<std::shared_ptr<Layer>>::iterator m_LayerInsert;

	};
	
}

