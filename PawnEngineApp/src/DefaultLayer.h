#pragma once

#include "Layer.h"

namespace pawn {
	
	class DefaultLayer : public Layer {
		
		public:
			virtual void OnInit() override;
			virtual void OnUpdate(Clock clock) override;
			virtual void OnRelease() override;

		private:
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
			std::shared_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
	};
	
}

