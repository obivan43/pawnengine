#pragma once

#include "PawnGraphics/graphics/GraphicsContext.h"

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
		
			bool Init(HWND handle, uint32_t width, uint32_t height) override final;
			void SwapBuffers() override final;

			ID3D11Device* GetDevice() const { return m_Device.Get(); }
			ID3D11DeviceContext* GetDeviceContext() const { return m_DeviceContext.Get(); }
			IDXGISwapChain* GetSwapChain() const { return m_SwapChain.Get(); }
			ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView.Get(); }
			ID3D11Texture2D* GetDepthStencilBuffer() const { return m_DepthStencilBuffer.Get(); }
			ID3D11DepthStencilView* GetDepthStencilView() const { return m_DepthStencilView.Get(); }
	
		private:
			HWND m_Handle;
			D3D_FEATURE_LEVEL m_FeatureLevel;
			Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
			Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
			Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilBuffer;
			Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
	};
	
}

#endif
