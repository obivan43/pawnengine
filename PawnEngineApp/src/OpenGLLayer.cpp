#include "pch.h"
#include "OpenGLLayer.h"
#include "Application.h"

#ifdef PAWN_OPENGL

namespace pawn {

	void OpenGLLayer::OnInit() {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();

		static Vertex vertices[] = {
			{ 0.0f,  0.5f},
			{ 0.5f, -0.5f},
			{-0.5f, -0.5f}
		};

		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float2 }
		};
	}

	void OpenGLLayer::OnUpdate(Clock clock) {
		glFlush();
	}

	void OpenGLLayer::OnRelease() {}
	
}

#endif
