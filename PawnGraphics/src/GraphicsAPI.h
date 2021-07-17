#pragma once

#include "PawnUtils/utils/codetools/Rtti.h"

#include <memory>

namespace pawn {

	class GraphicsContext;
	
	class GraphicsAPI : public Rtti {
		RTTI_DECLARATIONS(GraphicsAPI, Rtti)
		
		public:
			GraphicsAPI();
			GraphicsAPI(const GraphicsAPI& other) = default;
			GraphicsAPI(GraphicsAPI && other) noexcept = default;
		
			GraphicsAPI& operator=(const GraphicsAPI & other) = default;
			GraphicsAPI& operator=(GraphicsAPI && other) noexcept = default;
		
			virtual ~GraphicsAPI() = default;

			virtual void SetContext(std::shared_ptr<GraphicsContext>& context);

			virtual void SetClearColor(float r, float g, float b);
			virtual void Clear();
	
			static std::shared_ptr<GraphicsAPI> Create();
	};
	
}
