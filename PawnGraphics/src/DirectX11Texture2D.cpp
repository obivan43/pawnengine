#include "pch.h"
#include "DirectX11Texture2D.h"
#include "DirectX11Debug.h"
#include "DirectX11Context.h"

#ifdef PAWN_DIRECTX11

namespace pawn {

	void DirectX11Texture2D::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();
		deviceContext->PSSetShaderResources(0, 1, m_TextureView.GetAddressOf());
		deviceContext->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());
	}

	void DirectX11Texture2D::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();
		deviceContext->PSSetShaderResources(index, 1, m_TextureView.GetAddressOf());
		deviceContext->PSSetSamplers(index, 1, m_Sampler.GetAddressOf());
	}

	void DirectX11Texture2D::Init(
		std::shared_ptr<GraphicsContext>& context,
		const void* data, int32_t width,
		int32_t height,
		int32_t bitsPerPixel,
		const GraphicsTextureParams& params
	) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11Device* device = directX11Context->GetDevice();

		m_Width = width;
		m_Height = height;
		m_Params = params;
		m_BitsPerPixel = bitsPerPixel;

		D3D11_TEXTURE2D_DESC textureDescription = {};
		textureDescription.Width = width;
		textureDescription.Height = height;
		textureDescription.MipLevels = 1;
		textureDescription.ArraySize = 1;
		textureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDescription.SampleDesc.Count = 1;
		textureDescription.SampleDesc.Quality = 0;
		textureDescription.Usage = D3D11_USAGE_DEFAULT;
		textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDescription.CPUAccessFlags = 0;
		textureDescription.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA resourceData = {};
		resourceData.pSysMem = data;
		resourceData.SysMemPitch = width * sizeof(uint32_t);

		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		DirectX11Call(device->CreateTexture2D(&textureDescription, &resourceData, &texture))

		CONSOLE_INFO("Texture2D created")

		D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDescription = {};
		resourceViewDescription.Format = textureDescription.Format;
		resourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		resourceViewDescription.Texture2D.MostDetailedMip = 0;
		resourceViewDescription.Texture2D.MipLevels = 1;

		DirectX11Call(device->CreateShaderResourceView(texture.Get(), &resourceViewDescription, &m_TextureView))

		D3D11_SAMPLER_DESC samplerDescription = {};
		samplerDescription.Filter = params.m_FilterMode == GraphicsTextureFilter::LINEAR ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		DirectX11Call(device->CreateSamplerState(&samplerDescription, &m_Sampler))
	}

}

#endif
