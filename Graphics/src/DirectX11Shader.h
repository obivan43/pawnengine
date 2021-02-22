#pragma once

#include "GraphicsBindableResource.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>
#include <d3dcompiler.h>

namespace pawn {

	class DirectX11Shader : public GraphicsBindableResource {

		public:
			DirectX11Shader() = default;
			DirectX11Shader(const DirectX11Shader& other) = default;
			DirectX11Shader(DirectX11Shader&& other) noexcept = default;

			DirectX11Shader& operator=(const DirectX11Shader& other) = default;
			DirectX11Shader& operator=(DirectX11Shader&& other) noexcept = default;
		
			virtual ~DirectX11Shader() = default;
		
			bool InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName);
			bool InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName);
			bool Link();
			void Bind(std::shared_ptr<GraphicsContext>& context) override;

			ID3D11VertexShader* GetVertexShader() const { return m_VertexShader.Get(); }
			ID3D11PixelShader* GetPixelShader() const { return m_PixelShader.Get(); }

		private:
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	};

}

#endif
