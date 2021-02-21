#pragma once

namespace pawn {

	class Window;
	
	class GraphicsContext : public Rtti {
		RTTI_DECLARATIONS(GraphicsContext, Rtti)
	
		public:
			GraphicsContext() = default;
			GraphicsContext(const GraphicsContext& other) = default;
			GraphicsContext(GraphicsContext&& other) noexcept = default;

			GraphicsContext& operator=(const GraphicsContext& other) = default;
			GraphicsContext& operator=(GraphicsContext&& other) noexcept = default;

			virtual ~GraphicsContext() = default;

			virtual bool Init(const pawn::Window& window);
			virtual void SwapBuffers();
	};
	
}

