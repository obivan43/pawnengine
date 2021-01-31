#include "pch.h"
#include "GraphicsContext.h"

namespace pawn {
	
	bool GraphicsContext::Initialize(const pawn::Window& window) {
		(void)window;
		return true;
	}
	
	void GraphicsContext::SwapBuffers() {}
	
}

