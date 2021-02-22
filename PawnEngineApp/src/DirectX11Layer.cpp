#include "pch.h"
#include "DirectX11Layer.h"
#include "Application.h"

#ifdef PAWN_DIRECTX11

namespace pawn {

	void DirectX11Layer::OnInit() {
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
		
		m_VertexBuffer.reset(new DirectX11VertexBuffer());
		m_VertexShader.reset(new DirectX11VertexShader());
		m_PixelShader.reset(new DirectX11PixelShader());
		m_InputLayout.reset(new DirectX11InputLayout());
		m_GraphicsRenderer.reset(new DirectX11BasicRenderer(m_GraphicsContext));

		m_VertexBuffer->Init(m_GraphicsContext, vertices, std::size(vertices), sizeof(Vertex));
		m_VertexBuffer->Bind(m_GraphicsContext);
		
		m_VertexShader->Init(m_GraphicsContext, L"VertexShader.cso");
		m_PixelShader->Init(m_GraphicsContext, L"PixelShader.cso");

		m_VertexShader->Bind(m_GraphicsContext);
		m_PixelShader->Bind(m_GraphicsContext);

		m_InputLayout->Init(m_GraphicsContext, inputElements, m_VertexShader->GetBlob());
		m_InputLayout->Bind(m_GraphicsContext);
	}
	
	void DirectX11Layer::OnUpdate(Clock clock) {
		m_GraphicsRenderer->Draw(m_VertexBuffer);
	}
	
	void DirectX11Layer::OnRelease() {}
	
}

#endif
