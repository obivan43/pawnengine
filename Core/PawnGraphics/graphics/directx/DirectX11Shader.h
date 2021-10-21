#pragma once

#include "PawnGraphics/graphics/GraphicsShader.h"
#include "PawnSystem/system/windows/WindowsAPI.h"

#include <memory>

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn::graphics {

	class DirectX11Shader final : public GraphicsShader {

		public:
			DirectX11Shader() = default;
			DirectX11Shader(const DirectX11Shader& other) = default;
			DirectX11Shader(DirectX11Shader&& other) noexcept = default;

			DirectX11Shader& operator=(const DirectX11Shader& other) = default;
			DirectX11Shader& operator=(DirectX11Shader&& other) noexcept = default;

			bool Link();

			bool InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) override final;
			bool InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) override final;

			void Bind(std::shared_ptr<GraphicsContext>& context) override final;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override final;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override final;

			inline ID3D11VertexShader* GetVertexShader() const noexcept { return m_VertexShader.Get(); }
			inline ID3D11PixelShader* GetPixelShader() const noexcept { return m_PixelShader.Get(); }

			inline void* GetVertexShaderInfo() const override { return m_VertexShaderInfo.Get(); }
			inline void* GetPixelShaderInfo() const override { return m_PixelShaderInfo.Get(); }

		private:
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

			Microsoft::WRL::ComPtr<ID3DBlob> m_VertexShaderInfo;
			Microsoft::WRL::ComPtr<ID3DBlob> m_PixelShaderInfo;
	};

}

#endif
