﻿#include "pch.h"
#include "OpenglAPI.h"
#include "OpenglContext.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglAPI::OpenglAPI() : m_OpenglContext(nullptr) {}

	void OpenglAPI::SetContext(std::shared_ptr<GraphicsContext>& context) {
		GraphicsAPI::SetContext(context);
		m_OpenglContext = context->As<OpenglContext>();
	}

	void OpenglAPI::SetClearColor(float r, float g, float b) {
		glClearColor(r, g, b, 0.0f);
	}

	void OpenglAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
}

#endif