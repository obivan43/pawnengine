#include "pch.h"
#include "DirectX11BasicRenderer.h"
#include "DirectX11Context.h"

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	DirectX11BasicRenderer::DirectX11BasicRenderer(const std::shared_ptr<GraphicsContext>& context) : GraphicsRenderer(context) {}

	void DirectX11BasicRenderer::Draw(const std::shared_ptr<GraphicsBuffer>& buffer) {
		DirectX11Context* directX11Context = m_ContextCache->As<DirectX11Context>();
		ID3D11DeviceContext* context = directX11Context->GetDeviceContext();
		ID3D11RenderTargetView* renderTragetView = directX11Context->GetRenderTargetView();

		context->OMSetRenderTargets(1, &renderTragetView, nullptr);
		context->Draw(buffer->GetBufferSize(), 0);
	}
}

#endif
