#include "pch.h"
#include "DirectX11Context.h"
#include "DirectX11Debug.h"
#include "Window.h"
#include <comdef.h> 

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	DirectX11Context::DirectX11Context()
	: m_FeatureLevel(D3D_FEATURE_LEVEL_9_1)
	{}

	bool DirectX11Context::Init(const pawn::Window& window) {
		DXGI_MODE_DESC modeDescription = {};
		modeDescription.Width = window.GetWidth();
		modeDescription.Height = window.GetHeight();
		modeDescription.RefreshRate.Numerator = 144;
		modeDescription.RefreshRate.Denominator = 1;
		modeDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		modeDescription.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		modeDescription.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC swapChainDescription = {};
		swapChainDescription.BufferDesc = modeDescription;
		swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDescription.BufferCount = 2;
		swapChainDescription.SampleDesc.Count = 1;
		swapChainDescription.SampleDesc.Quality = 0;
		swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDescription.Flags = 0;
		swapChainDescription.OutputWindow = static_cast<HWND>(window.GetNativeHandle());
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

		UINT deviceFlags = 0;

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

		D3D11_TEXTURE2D_DESC depthStencilDescription = {};
		depthStencilDescription.Width = window.GetWidth();
		depthStencilDescription.Height = window.GetHeight();
		depthStencilDescription.MipLevels = 1;
		depthStencilDescription.ArraySize = 1;
		depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDescription.SampleDesc.Count = 1;
		depthStencilDescription.SampleDesc.Quality = 0;
		depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDescription.CPUAccessFlags = 0;
		depthStencilDescription.MiscFlags = 0;

		DirectX11Call(m_Device->CreateTexture2D(&depthStencilDescription, nullptr, &m_DepthStencilBuffer))
		DirectX11Call(m_Device->CreateDepthStencilView(m_DepthStencilBuffer.Get(), nullptr, &m_DepthStencilView))

		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width = static_cast<float>(window.GetWidth());
		viewPort.Height = static_cast<float>(window.GetHeight());
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewPort);

		IDXGIDevice* dxgiDevice;
		m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		IDXGIAdapter* adapter;
		dxgiDevice->GetAdapter(&adapter);
		DXGI_ADAPTER_DESC adapterDesc;
		adapter->GetDesc(&adapterDesc);

		_bstr_t b(adapterDesc.Description);
		const char* description = b;

		spdlog::info("*********************************************");
		if(adapterDesc.VendorId == 0x10DE) {
			spdlog::info("Vendor: NVIDIA Corporation");
		} else if(adapterDesc.VendorId == 0x1002 || adapterDesc.VendorId == 0x1022) {
			spdlog::info("Vendor: Advanced Micro Devices");
		}
		else if(adapterDesc.VendorId == 0x163C || adapterDesc.VendorId == 0x8086 || adapterDesc.VendorId == 0x8087) {
			spdlog::info("Vendor: Intel Corporation");
		}
		spdlog::info("Videocard: {}", description);
		spdlog::info("*********************************************");
		
		spdlog::info("DirectX11 context initialized");
		
		return true;
	}

	void DirectX11Context::SwapBuffers() {
		m_SwapChain->Present(1, 0);
	}
}

#endif
