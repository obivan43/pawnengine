﻿#include "pch.h"
#include "OpenGLLayer.h"
#include "Application.h"

#ifdef PAWN_OPENGL

namespace pawn {

	void OpenGLLayer::OnInit() {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();

		static Vertex vertices[] = {
			{ 0.0f,  0.5f },
			{ 0.5f, -0.5f },
			{-0.5f, -0.5f }
		};

		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float2 }
		};

		m_VertexBuffer.reset(new OpenglVertexBuffer());
		m_InputLayout.reset(new OpenglInputLayout());
		m_GraphicsRenderer.reset(new OpenglBasicRenderer(m_GraphicsContext));

		m_VertexBuffer->Init(m_GraphicsContext, vertices, std::size(vertices), sizeof(Vertex));
		m_VertexBuffer->Bind(m_GraphicsContext);

		m_InputLayout->Init(m_GraphicsContext, inputElements, nullptr);
		m_InputLayout->Bind(m_GraphicsContext);
	}

	void OpenGLLayer::OnUpdate(Clock clock) {
		UNUSED(clock)
		m_GraphicsRenderer->Draw(m_VertexBuffer);
	}

	void OpenGLLayer::OnRelease() {}

	void OpenGLLayer::HandleEvent(Event& e) {
		if (e.GetType() == EventTypeEnum::WindowResize) {
			OpenglAPI* openglAPI = m_GraphicsAPI->As<OpenglAPI>();
			WindowResizeEvent& resizeEvent = reinterpret_cast<WindowResizeEvent&>(e);
			openglAPI->SetViewport(resizeEvent.m_Width, resizeEvent.m_Height);
		}
	}
	
}

#endif
