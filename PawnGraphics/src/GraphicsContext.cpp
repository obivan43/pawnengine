#include "pch.h"
#include "GraphicsContext.h"
#include "Directx11Context.h"

namespace pawn {
	
	std::shared_ptr<GraphicsContext> GraphicsContext::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsContext>(new DirectX11Context());
#else
		return std::shared_ptr<GraphicsContext>(new GraphicsContext());
#endif
	}

	bool GraphicsContext::Init(HWND handle, uint32_t width, uint32_t height) {
		UNUSED(handle)
		UNUSED(width)
		UNUSED(height)

		CONSOLE_ERROR("Graphics context not created");
	
		return true;
	}
	
	void GraphicsContext::SwapBuffers() {}
	
}

