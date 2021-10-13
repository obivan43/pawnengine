#pragma once

#include "PawnGraphics/graphics/GraphicsShader.h"

#include "PawnSystem/system/windows/WindowsAPI.h"

#include <memory>

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	namespace graphics {

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
				void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;
				void Unbind(std::shared_ptr<GraphicsContext>& context) override;

				ID3D11VertexShader* GetVertexShader() const { return m_VertexShader.Get(); }
				ID3D11PixelShader* GetPixelShader() const { return m_PixelShader.Get(); }

				void* GetVertexShaderInfo() const override { return m_VertexShaderInfo.Get(); }
				void* GetPixelShaderInfo() const override { return m_PixelShaderInfo.Get(); }

			private:
				Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
				Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

				Microsoft::WRL::ComPtr<ID3DBlob> m_VertexShaderInfo;
				Microsoft::WRL::ComPtr<ID3DBlob> m_PixelShaderInfo;
		};

	}

}

#endif
