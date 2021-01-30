#include "pch.h"
#include "GraphicsContext.h"

namespace pawn {
	
	bool GraphicsContext::Initialize(const HWND hwnd) {
		(void)hwnd;
		return true;
	}
	
	void GraphicsContext::SwapBuffers() {}
	
}

