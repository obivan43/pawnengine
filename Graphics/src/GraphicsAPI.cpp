#include "pch.h"
#include "GraphicsAPI.h"
#include "GraphicsContext.h"

namespace pawn {

	void GraphicsAPI::SetClearColor(float r, float g, float b) {
		UNUSED(r)
		UNUSED(g)
		UNUSED(b)

		spdlog::get("console")->error("Graphics API not selected");
	}
	
	void GraphicsAPI::Clear() {}
	
}