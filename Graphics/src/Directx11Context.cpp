#include "pch.h"
#include "DirectX11Context.h"
#include "DirectX11Debug.h"
#include "Window.h"

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	DirectX11Context::DirectX11Context()
	: m_FeatureLevel(D3D_FEATURE_LEVEL_9_1),
	m_Device(nullptr),
	m_DeviceContext(nullptr),
	m_SwapChain(nullptr),
	m_RenderTargetView(nullptr)
	{}

	DirectX11Context::~DirectX11Context() {
		if (m_RenderTargetView != nullptr) {
			m_RenderTargetView->Release();
		}

		if(m_SwapChain != nullptr) {
			m_SwapChain->Release();
		}
		
		if (m_DeviceContext != nullptr) {
			m_DeviceContext->Release();
		}
		
		if(m_Device != nullptr) {
			m_Device->Release();
		}
	}

	bool DirectX11Context::Initialize(const pawn::Window& window) {
		DXGI_MODE_DESC modeDescription = {};
		modeDescription.Width = 800;
		modeDescription.Height = 600;
		modeDescription.RefreshRate.Numerator = 144;
		modeDescription.RefreshRate.Denominator = 1;
		modeDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		modeDescription.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		modeDescription.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC swapChainDescription = {};
		swapChainDescription.BufferDesc = modeDescription;
		swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDescription.BufferCount = 1;
		swapChainDescription.SampleDesc.Count = 1;
		swapChainDescription.SampleDesc.Quality = 0;
		swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDescription.Flags = 0;
		swapChainDescription.OutputWindow = reinterpret_cast<HWND>(window.GetNativeHandle());
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

		ID3D11Resource* buffer = nullptr;
		DirectX11Call(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&buffer)))
		DirectX11Call(m_Device->CreateRenderTargetView(buffer, nullptr, &m_RenderTargetView));
		buffer->Release();
		
		return true;
	}

	void DirectX11Context::SwapBuffers() {
		m_SwapChain->Present(1, 0);
	}
	
}

#endif
