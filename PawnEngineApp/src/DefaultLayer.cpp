#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"
#include "d3dcompiler.h"

#ifdef PAWN_DIRECTX11

namespace pawn {

	void DefaultLayer::OnInit() {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();

		static Vertex vertices[] = {
			{ 0.0f,  0.5f},
			{ 0.5f, -0.5f},
			{-0.5f, -0.5f}
		};

		DirectX11Context* directX11Context = m_GraphicsContext->As<DirectX11Context>();
		ID3D11Device* device = directX11Context->GetDevice();
		ID3D11DeviceContext* context = directX11Context->GetDeviceContext();
		
		DirectX11VertexBuffer* vertexBuffer = new DirectX11VertexBuffer();
		vertexBuffer->Initialize(
			device,
			vertices,
			std::size(vertices),
			sizeof(Vertex)
		);
		
		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float2 }
		};
		
		m_VertexBuffer.reset(vertexBuffer);
		m_VertexShader.reset(new DirectX11VertexShader());
		m_PixelShader.reset(new DirectX11PixelShader());
		m_InputLayout.reset(new DirectX11InputLayout());
		
		m_VertexBuffer->Bind(m_GraphicsContext);
		
		m_VertexShader->Init(m_GraphicsContext, L"VertexShader.cso");
		m_PixelShader->Init(m_GraphicsContext, L"PixelShader.cso");

		m_VertexShader->Bind(m_GraphicsContext);
		m_PixelShader->Bind(m_GraphicsContext);

		m_InputLayout->Init(m_GraphicsContext, m_VertexShader->GetBlob(), inputElements);
		m_InputLayout->Bind(m_GraphicsContext);
	}
	
	void DefaultLayer::OnUpdate(Clock clock) {
		DirectX11Context* directX11Context = m_GraphicsContext->As<DirectX11Context>();
		ID3D11DeviceContext* context = directX11Context->GetDeviceContext();
		ID3D11RenderTargetView* renderTragetView = directX11Context->GetRenderTargetView();
		
		context->OMSetRenderTargets(1, &renderTragetView, nullptr);
		context->Draw(m_VertexBuffer->GetBufferSize(), 0);
	}
	
	void DefaultLayer::OnRelease() {}
	
}

#endif
