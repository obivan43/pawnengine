#pragma once

namespace pawn {
	
	class GraphicsContext {
		
		public:
			GraphicsContext() = default;
			GraphicsContext(const GraphicsContext& other) = default;
			GraphicsContext(GraphicsContext&& other) noexcept = default;

			GraphicsContext& operator=(const GraphicsContext& other) = default;
			GraphicsContext& operator=(GraphicsContext&& other) noexcept = default;

			virtual ~GraphicsContext() = default;

			virtual void Initialize();
			virtual void SwapBuffers();
	};
	
}

