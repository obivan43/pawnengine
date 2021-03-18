#include "pch.h"
#include "DirectX11Renderer.h"
#include "DirectX11Context.h"
#include "GraphicsBuffer.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	void DirectX11Renderer::Draw(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& buffer) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();
		ID3D11RenderTargetView* renderTragetView = directX11Context->GetRenderTargetView();
		ID3D11DepthStencilView* depthStencilView = directX11Context->GetDepthStencilView();

		deviceContext->OMSetRenderTargets(1, &renderTragetView, depthStencilView);
		deviceContext->Draw(buffer->GetBufferSize(), 0);
	}

	void DirectX11Renderer::DrawIndexed(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& indexBuffer) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();
		ID3D11RenderTargetView* renderTragetView = directX11Context->GetRenderTargetView();
		ID3D11DepthStencilView* depthStencilView = directX11Context->GetDepthStencilView();

		deviceContext->OMSetRenderTargets(1, &renderTragetView, depthStencilView);
		deviceContext->DrawIndexed(indexBuffer->GetBufferSize(), 0, 0);
	}
}

#endif
