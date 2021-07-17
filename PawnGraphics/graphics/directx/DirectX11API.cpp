#include "DirectX11API.h"
#include "DirectX11Context.h"

#include "PawnUtils/utils/logger/Logger.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	namespace graphics {

		DirectX11API::DirectX11API()
			: m_clearColor{ 0.0f, 0.0f, 0.0f, 1.0f }, m_DirectX11Context(nullptr)
		{}

		void DirectX11API::SetContext(std::shared_ptr<GraphicsContext>& context) {
			m_DirectX11Context = context->As<DirectX11Context>();
			CONSOLE_INFO("DirectX11API initialized with context")
		}

		void DirectX11API::SetClearColor(float r, float g, float b) {
			m_clearColor[0] = r;
			m_clearColor[1] = g;
			m_clearColor[2] = b;
		}

		void DirectX11API::Clear() {
			m_DirectX11Context->m_DeviceContext->ClearRenderTargetView(m_DirectX11Context->m_RenderTargetView.Get(), m_clearColor);
			m_DirectX11Context->m_DeviceContext->ClearDepthStencilView(m_DirectX11Context->m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
		}

	}
}

#endif
