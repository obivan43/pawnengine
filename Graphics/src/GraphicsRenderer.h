#pragma once

#include "GraphicsBuffer.h"
#include "GraphicsContext.h"

namespace pawn {
	
	class GraphicsRenderer {
		
		public:
			GraphicsRenderer(const std::shared_ptr<GraphicsContext>& context);
			GraphicsRenderer(const GraphicsRenderer& other) = default;
			GraphicsRenderer(GraphicsRenderer&& other) noexcept = default;

			GraphicsRenderer& operator=(const GraphicsRenderer& other) = default;
			GraphicsRenderer& operator=(GraphicsRenderer&& other) noexcept = default;

			~GraphicsRenderer() = default;
		
			virtual void Draw(const std::shared_ptr<GraphicsBuffer>& buffer);
	
		protected:
			std::shared_ptr<GraphicsContext> m_ContextCache;
	};
	
}
