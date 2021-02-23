#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglAPI.h"
#include "OpenglContext.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglAPI::OpenglAPI() : m_OpenglContext(nullptr) {}

	void OpenglAPI::SetContext(std::shared_ptr<GraphicsContext>& context) {
		GraphicsAPI::SetContext(context);
		m_OpenglContext = context->As<OpenglContext>();
		spdlog::get("console")->info("OpenglAPI initialized with context");
	}

	void OpenglAPI::SetClearColor(float r, float g, float b) {
		OpenglCall(glClearColor(r, g, b, 0.0f))
	}

	void OpenglAPI::Clear() {
		OpenglCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
	}

	void OpenglAPI::SetViewport(uint32_t width, uint32_t height) {
		OpenglCall(glViewport(0, 0, width, height))
	}
	
}

#endif
