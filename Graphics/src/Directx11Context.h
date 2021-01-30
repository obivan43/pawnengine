#pragma once

#include "GraphicsContext.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {
	
	class DirectX11Context : public GraphicsContext {
		
		public:
			DirectX11Context();
			DirectX11Context(const DirectX11Context& other) = default;
			DirectX11Context(DirectX11Context&& other) noexcept = default;
			
			DirectX11Context& operator=(const DirectX11Context& other) = default;
			DirectX11Context& operator=(DirectX11Context&& other) noexcept = default;

			~DirectX11Context() override;
		
			virtual bool Initialize(const HWND hwnd) override final;
			virtual void SwapBuffers() override final;

		private:
			D3D_FEATURE_LEVEL m_FeatureLevel;
			ID3D11Device* m_Device;
			ID3D11DeviceContext* m_DeviceContext;
			IDXGISwapChain* m_SwapChain;
			ID3D11RenderTargetView* m_TargetView;
	};
	
}

#endif
