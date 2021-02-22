#include "pch.h"
#include "DirectX11API.h"
#include "DirectX11Context.h"

#include <d3d11.h>

#ifdef PAWN_DIRECTX11

namespace pawn {

	DirectX11API::DirectX11API()
	: m_clearColor{0.0f, 0.0f, 0.0f, 1.0f}, m_DirectX11Context(nullptr)
	{}

	
	void DirectX11API::SetContext(std::shared_ptr<GraphicsContext>& context) {
		GraphicsAPI::SetContext(context);
		m_DirectX11Context = context->As<DirectX11Context>();
		spdlog::get("console")->info("DirectX11API initialized with context");
	}

	void DirectX11API::SetClearColor(float r, float g, float b) {
		m_clearColor[0] = r;
		m_clearColor[1] = g;
		m_clearColor[2] = b;
	}

	void DirectX11API::Clear() {
		m_DirectX11Context->m_DeviceContext->ClearRenderTargetView(m_DirectX11Context->m_RenderTargetView.Get(), m_clearColor);
	}
}

#endif
