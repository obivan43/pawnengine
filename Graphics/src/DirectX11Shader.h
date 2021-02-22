#pragma once

#include "GraphicsShader.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	class DirectX11Shader : public GraphicsShader {

		public:
			DirectX11Shader() = default;
			DirectX11Shader(const DirectX11Shader& other) = default;
			DirectX11Shader(DirectX11Shader&& other) noexcept = default;

			DirectX11Shader& operator=(const DirectX11Shader& other) = default;
			DirectX11Shader& operator=(DirectX11Shader&& other) noexcept = default;
		
			bool InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) override;
			bool InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) override;
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
