#pragma once

#include <memory>

namespace pawn {
	
	class GraphicsContext;
	class GraphicsBuffer;

	class GraphicsRenderer {
		
		public:
			GraphicsRenderer() = default;
			GraphicsRenderer(const GraphicsRenderer& other) = default;
			GraphicsRenderer(GraphicsRenderer&& other) noexcept = default;

			GraphicsRenderer& operator=(const GraphicsRenderer& other) = default;
			GraphicsRenderer& operator=(GraphicsRenderer&& other) noexcept = default;

			virtual ~GraphicsRenderer() = default;
		
			virtual void Draw(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& buffer);
			virtual void DrawIndexed(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& IndexBuffer);

			static std::shared_ptr<GraphicsRenderer> Create();
	};
	
}
