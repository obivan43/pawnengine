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
		ID3D11RenderTargetView* renderTragetView = directX11Context->GetRenderTargetView();
		
		DirectX11VertexBuffer* vertexBuffer = new DirectX11VertexBuffer();
		vertexBuffer->Initialize(
			device,
			vertices,
			std::size(vertices),
			sizeof(Vertex)
		);
		m_VertexBuffer.reset(vertexBuffer);
		m_VertexBuffer->Bind(m_GraphicsContext);

		D3DReadFileToBlob(L"PixelShader.cso", &m_Blob);
		DirectX11Call(device->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PixelShader))
		context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

		D3DReadFileToBlob(L"VertexShader.cso", &m_Blob);
		DirectX11Call(device->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_VertexShader))
		context->VSSetShader(m_VertexShader.Get(), nullptr, 0);

		D3D11_INPUT_ELEMENT_DESC inputDescription[] = {
			{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		DirectX11Call(device->CreateInputLayout(
			inputDescription,
			static_cast<UINT>(std::size(inputDescription)),
			m_Blob->GetBufferPointer(),
			m_Blob->GetBufferSize(),
			&m_InputLayout
		))

		context->IASetInputLayout(m_InputLayout.Get());
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
