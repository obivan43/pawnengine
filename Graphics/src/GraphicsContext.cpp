#include "pch.h"
#include "GraphicsContext.h"

namespace pawn {
	
	bool GraphicsContext::Init(const pawn::Window& window) {
		UNUSED(window)
		return true;
	}
	
	void GraphicsContext::SwapBuffers() {}
	
}

