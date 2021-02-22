#include "pch.h"
#include "GraphicsContext.h"

namespace pawn {
	
	bool GraphicsContext::Init(const pawn::Window& window) {
		UNUSED(window)

		spdlog::get("console")->error("Graphics context not created");
	
		return true;
	}
	
	void GraphicsContext::SwapBuffers() {}
	
}

