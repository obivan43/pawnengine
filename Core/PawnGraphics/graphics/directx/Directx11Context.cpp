#include <comdef.h> // Need to be first include

#include "DirectX11Context.h"

#include "PawnGraphics/graphics/directx/debug/DirectX11Debug.h"

#include "PawnUtils/utils/logger/Logger.h"

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	namespace graphics {

		DirectX11Context::DirectX11Context()
			: m_FeatureLevel(D3D_FEATURE_LEVEL_9_1)
		{}

		bool DirectX11Context::Init(HWND handle, uint32_t width, uint32_t height) {
			m_Handle = handle;

			DXGI_MODE_DESC modeDescription{};
			modeDescription.Width = width;
			modeDescription.Height = height;
			modeDescription.RefreshRate.Numerator = 144;
			modeDescription.RefreshRate.Denominator = 1;
			modeDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			modeDescription.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			modeDescription.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			DXGI_SWAP_CHAIN_DESC swapChainDescription{};
			swapChainDescription.BufferDesc = modeDescription;
			swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDescription.BufferCount = 2;
			swapChainDescription.SampleDesc.Count = 1;
			swapChainDescription.SampleDesc.Quality = 0;
			swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapChainDescription.Flags = 0;
			swapChainDescription.OutputWindow = m_Handle;
			swapChainDescription.Windowed = true;

			D3D_FEATURE_LEVEL FeatureLevels[] = {
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1
			};

			UINT deviceFlags{ 0 };

#if defined(DEBUG) || defined(_DEBUG)
			deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif		
			DirectX11Call(D3D11CreateDeviceAndSwapChain(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				deviceFlags,
				FeatureLevels,
				ARRAYSIZE(FeatureLevels),
				D3D11_SDK_VERSION,
				&swapChainDescription,
				&m_SwapChain,
				&m_Device,
				&m_FeatureLevel,
				&m_DeviceContext
			))

			Microsoft::WRL::ComPtr<ID3D11Resource> buffer;
			DirectX11Call(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &buffer))
			DirectX11Call(m_Device->CreateRenderTargetView(buffer.Get(), nullptr, &m_RenderTargetView))

			D3D11_DEPTH_STENCIL_DESC depthStencilStateDescription {};
			depthStencilStateDescription.DepthEnable = TRUE;
			depthStencilStateDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilStateDescription.DepthFunc = D3D11_COMPARISON_LESS;

			Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
			DirectX11Call(m_Device->CreateDepthStencilState(&depthStencilStateDescription, &depthStencilState))
			m_DeviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);

			D3D11_TEXTURE2D_DESC depthStencilDescription{};
			depthStencilDescription.Width = width;
			depthStencilDescription.Height = height;
			depthStencilDescription.MipLevels = 1;
			depthStencilDescription.ArraySize = 1;
			depthStencilDescription.Format = DXGI_FORMAT_D32_FLOAT;
			depthStencilDescription.SampleDesc.Count = 1;
			depthStencilDescription.SampleDesc.Quality = 0;
			depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDescription.CPUAccessFlags = 0;
			depthStencilDescription.MiscFlags = 0;

			DirectX11Call(m_Device->CreateTexture2D(&depthStencilDescription, nullptr, &m_DepthStencilBuffer))

			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription {};
			depthStencilViewDescription.Format = DXGI_FORMAT_D32_FLOAT;
			depthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDescription.Texture2D.MipSlice = 0;

			DirectX11Call(m_Device->CreateDepthStencilView(m_DepthStencilBuffer.Get(), &depthStencilViewDescription, &m_DepthStencilView))

			m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

			m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			D3D11_VIEWPORT viewPort{};
			viewPort.TopLeftX = 0.0f;
			viewPort.TopLeftY = 0.0f;
			viewPort.Width = static_cast<float>(width);
			viewPort.Height = static_cast<float>(height);
			viewPort.MinDepth = 0.0f;
			viewPort.MaxDepth = 1.0f;
			m_DeviceContext->RSSetViewports(1, &viewPort);

			D3D11_RASTERIZER_DESC rasterizerDescription{};
			rasterizerDescription.FillMode = D3D11_FILL_SOLID;
			rasterizerDescription.CullMode = D3D11_CULL_FRONT;

			Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
			DirectX11Call(m_Device->CreateRasterizerState(&rasterizerDescription, &rasterizerState))
			m_DeviceContext->RSSetState(rasterizerState.Get());

			IDXGIDevice* dxgiDevice{ nullptr };
			IDXGIAdapter* adapter{ nullptr };
			DXGI_ADAPTER_DESC adapterDesc{};

			m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
			dxgiDevice->GetAdapter(&adapter);
			adapter->GetDesc(&adapterDesc);

			_bstr_t b(adapterDesc.Description);
			const char* description{ b };

			CONSOLE_INFO("*********************************************")
			if (adapterDesc.VendorId == 0x10DE) {
				CONSOLE_INFO("Vendor: NVIDIA Corporation")
			}
			else if (adapterDesc.VendorId == 0x1002 || adapterDesc.VendorId == 0x1022) {
				CONSOLE_INFO("Vendor: Advanced Micro Devices")
			}
			else if (adapterDesc.VendorId == 0x163C || adapterDesc.VendorId == 0x8086 || adapterDesc.VendorId == 0x8087) {
				CONSOLE_INFO("Vendor: Intel Corporation")
			}
			CONSOLE_INFO("Videocard: {}", description)
			CONSOLE_INFO("*********************************************")
			CONSOLE_INFO("DirectX11 context initialized")

			return true;
		}

		void DirectX11Context::SwapBuffers() {
			DirectX11Call(m_SwapChain->Present(1, 0))
		}

	}

}

#endif
