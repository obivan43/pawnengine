#include "pch.h"
#include "GraphicsAPI.h"
#include "GraphicsContext.h"
#include "DirectX11API.h"

namespace pawn {

	GraphicsAPI::GraphicsAPI() {}

	std::shared_ptr<GraphicsAPI> GraphicsAPI::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsAPI>(new DirectX11API());
#else
		return std::shared_ptr<GraphicsAPI>(new GraphicsAPI());
#endif
	}

	void GraphicsAPI::SetContext(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}

	void GraphicsAPI::SetClearColor(float r, float g, float b) {
		UNUSED(r)
		UNUSED(g)
		UNUSED(b)

		CONSOLE_ERROR("Graphics API not selected");
	}
	
	void GraphicsAPI::Clear() {}
	
}