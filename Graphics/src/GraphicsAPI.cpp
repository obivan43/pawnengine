#include "pch.h"
#include "GraphicsAPI.h"
#include "GraphicsContext.h"
#include "OpenglAPI.h"
#include "DirectX11API.h"

namespace pawn {

	std::shared_ptr<GraphicsAPI> GraphicsAPI::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsAPI>(new DirectX11API());
#elif PAWN_OPENGL
		return std::shared_ptr<GraphicsAPI>(new OpenglAPI());
#else
		return std::shared_ptr<GraphicsAPI>(new GraphicsAPI());
#endif
	}

	void GraphicsAPI::SetClearColor(float r, float g, float b) {
		UNUSED(r)
		UNUSED(g)
		UNUSED(b)

		spdlog::get("console")->error("Graphics API not selected");
	}
	
	void GraphicsAPI::Clear() {}
	
}