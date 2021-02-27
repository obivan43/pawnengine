#pragma once

#include <memory>

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

			virtual ~GraphicsRenderer() = default;
		
			virtual void Draw(const std::shared_ptr<GraphicsBuffer>& buffer);
			virtual void DrawIndexed(const std::shared_ptr<GraphicsBuffer>& IndexBuffer);

			static std::shared_ptr<GraphicsRenderer> Create(std::shared_ptr<GraphicsContext>& context);
	
		protected:
			std::shared_ptr<GraphicsContext> m_ContextCache;
	};
	
}
