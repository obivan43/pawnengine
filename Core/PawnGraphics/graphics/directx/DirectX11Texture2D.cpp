#include "DirectX11Texture2D.h"

#include "DirectX11Context.h"

#include "PawnGraphics/graphics/directx/debug/DirectX11Debug.h"
#include "PawnUtils/utils/logger/Logger.h"

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

	void DirectX11Texture2D::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();

		deviceContext->PSSetShaderResources(0, 1, m_TextureView.GetAddressOf());
		deviceContext->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());
		m_LastBoundIndex = 0;
	}

	void DirectX11Texture2D::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();

		deviceContext->PSSetShaderResources(index, 1, m_TextureView.GetAddressOf());
		deviceContext->PSSetSamplers(index, 1, m_Sampler.GetAddressOf());
		m_LastBoundIndex = index;
	}

	void DirectX11Texture2D::Unbind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> nullView;
		deviceContext->PSSetShaderResources(m_LastBoundIndex, 1, nullView.GetAddressOf());
	}

	void DirectX11Texture2D::Init(
		std::shared_ptr<GraphicsContext>& context,
		const void* data, int32_t width,
		int32_t height,
		int32_t bitsPerPixel,
		const GraphicsTextureParams& params
	) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11Device* device{ directX11Context->GetDevice() };

		m_Width = width;
		m_Height = height;
		m_Params = params;
		m_BitsPerPixel = bitsPerPixel;
		m_LastBoundIndex = 0;

		D3D11_TEXTURE2D_DESC textureDescription{};
		textureDescription.Width = width;
		textureDescription.Height = height;
		textureDescription.MipLevels = 0;
		textureDescription.ArraySize = 1;
		textureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDescription.SampleDesc.Count = 1;
		textureDescription.SampleDesc.Quality = 0;
		textureDescription.Usage = D3D11_USAGE_DEFAULT;
		textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		textureDescription.CPUAccessFlags = 0;
		textureDescription.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		DirectX11Call(device->CreateTexture2D(&textureDescription, nullptr, &texture))
		directX11Context->GetDeviceContext()->UpdateSubresource(texture.Get(), 0, nullptr, data, width * sizeof(uint32_t), 0);

		CONSOLE_INFO("Texture2D created")

		D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDescription {};
		resourceViewDescription.Format = textureDescription.Format;
		resourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		resourceViewDescription.Texture2D.MostDetailedMip = 0;
		resourceViewDescription.Texture2D.MipLevels = -1;

		DirectX11Call(device->CreateShaderResourceView(texture.Get(), &resourceViewDescription, &m_TextureView))
		directX11Context->GetDeviceContext()->GenerateMips(m_TextureView.Get());

		D3D11_SAMPLER_DESC samplerDescription {};
		samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescription.MipLODBias = 0.0f;
		samplerDescription.MinLOD = 0.0f;
		samplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

		switch (params.m_FilterMode) {
			case GraphicsTextureFilter::LINEAR:
				samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				break;
			case GraphicsTextureFilter::NEAREST:
				samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
				break;
			case GraphicsTextureFilter::ANISOTROPIC: {
				samplerDescription.Filter = D3D11_FILTER_ANISOTROPIC;
				samplerDescription.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
			}
				break;
			default:
				samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				break;
		}

		DirectX11Call(device->CreateSamplerState(&samplerDescription, &m_Sampler))
	}

}

#endif
