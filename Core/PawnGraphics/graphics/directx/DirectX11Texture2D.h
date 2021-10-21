#pragma once

#include "PawnGraphics/graphics/GraphicsTexture2D.h"
#include "PawnSystem/system/windows/WindowsAPI.h"

#include <memory>

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn::graphics {

	class DirectX11Texture2D final : public GraphicsTexture2D {

		public:
			DirectX11Texture2D() = default;
			DirectX11Texture2D(const DirectX11Texture2D& other) = default;
			DirectX11Texture2D(DirectX11Texture2D&& other) noexcept = default;

			DirectX11Texture2D& operator=(const DirectX11Texture2D& other) = default;
			DirectX11Texture2D& operator=(DirectX11Texture2D&& other) noexcept = default;

			void Init(
				std::shared_ptr<GraphicsContext>& context,
				const void* data,
				int32_t width,
				int32_t height,
				int32_t bitsPerPixel,
				const GraphicsTextureParams& params
			) override final;

			void Bind(std::shared_ptr<GraphicsContext>& context) override final;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override final;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override final;

			inline void* GetTexture() override final { return m_TextureView.Get(); }

		private:
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureView;
			Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
			uint32_t m_LastBoundIndex;
	};

}

#endif
