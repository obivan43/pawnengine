#pragma once

#include "GraphicsContext.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	class DirectX11API;
	
	class DirectX11Context : public GraphicsContext {

		friend DirectX11API;
		
		public:
			DirectX11Context();
			DirectX11Context(const DirectX11Context& other) = default;
			DirectX11Context(DirectX11Context&& other) noexcept = default;
			
			DirectX11Context& operator=(const DirectX11Context& other) = default;
			DirectX11Context& operator=(DirectX11Context&& other) noexcept = default;

			~DirectX11Context() override;
		
			virtual bool Initialize(const pawn::Window& window) override final;
			virtual void SwapBuffers() override final;

			ID3D11Device* GetDevice() const { return m_Device; }
			ID3D11DeviceContext* GetDeviceContext() const { return m_DeviceContext; }
			IDXGISwapChain* GetSwapChain() const { return m_SwapChain; }
			ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView; }
	
		private:
			D3D_FEATURE_LEVEL m_FeatureLevel;
			ID3D11Device* m_Device;
			ID3D11DeviceContext* m_DeviceContext;
			IDXGISwapChain* m_SwapChain;
			ID3D11RenderTargetView* m_RenderTargetView;
	};
	
}

#endif
