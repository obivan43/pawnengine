#include "GraphicsAPI.h"

#include "GraphicsContext.h"

#include "directx/DirectX11API.h"

#include "PawnUtils/utils/codetools/Macros.h"
#include "PawnUtils/utils/logger/Logger.h"

namespace pawn::graphics {

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
