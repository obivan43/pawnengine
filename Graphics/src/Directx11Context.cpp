#include "pch.h"
#include "DirectX11Context.h"

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	DirectX11Context::DirectX11Context()
	: m_FeatureLevel(D3D_FEATURE_LEVEL_9_1), m_Device(nullptr), m_DeviceContext(nullptr) {}

	DirectX11Context::~DirectX11Context() {
		if (m_DeviceContext != nullptr) {
			m_DeviceContext->Release();
		}
		
		if(m_Device != nullptr) {
			m_Device->Release();
		}
	}

	bool DirectX11Context::Initialize() {
		HRESULT result = E_FAIL;
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
		result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			deviceFlags,
			FeatureLevels,
			ARRAYSIZE(FeatureLevels),
			D3D11_SDK_VERSION,
			&m_Device, 
			&m_FeatureLevel,
			&m_DeviceContext
		);

		if(FAILED(result)) {
			std::cout << "Failed to create D3D device" << std::endl;
			return false;
		}

		if (m_FeatureLevel != D3D_FEATURE_LEVEL_11_1) {
			std::cout << "D3D_FEATURE_LEVEL_11_1 Feature level not supported" << std::endl;
			return false;
		}

		return true;
	}

	void DirectX11Context::SwapBuffers() {}
	
}

#endif
