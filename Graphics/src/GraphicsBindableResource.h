#pragma once

#include "GraphicsContext.h"

namespace pawn {
	
	class GraphicsBindableResource {
		
		public:
			virtual ~GraphicsBindableResource() = default;
		
			virtual void Bind(std::shared_ptr<GraphicsContext>& context) = 0;

	};

}
