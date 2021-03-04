#include "pch.h"
#include "GraphicsContext.h"
#include "OpenglContext.h"
#include "DirectX11Context.h"

namespace pawn {
	
	std::shared_ptr<GraphicsContext> GraphicsContext::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsContext>(new DirectX11Context());
#elif PAWN_OPENGL
		return std::shared_ptr<GraphicsContext>(new OpenglContext());
#else
		return std::shared_ptr<GraphicsContext>(new GraphicsContext());
#endif
	}

	bool GraphicsContext::Init(const pawn::Window& window) {
		UNUSED(window)

		spdlog::get("console")->error("Graphics context not created");
	
		return true;
	}
	
	void GraphicsContext::SwapBuffers() {}
	
}

