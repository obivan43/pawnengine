#pragma once

#include "GraphicsContext.h"

namespace pawn {
	
	class GraphicsBindableResource {
		
		public:
			virtual void Bind(std::shared_ptr<GraphicsContext>& context) = 0;
			virtual void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) = 0;

	};

}
