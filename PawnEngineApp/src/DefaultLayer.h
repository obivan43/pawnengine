#pragma once

#include "Layer.h"

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	class DefaultLayer : public Layer {
		
		public:
			DefaultLayer() = default;
			DefaultLayer(const DefaultLayer& other) = delete;
			DefaultLayer(DefaultLayer&& other) noexcept = default;

			DefaultLayer& operator=(const DefaultLayer& other) = delete;
			DefaultLayer& operator=(DefaultLayer&& other) noexcept = delete;
		
			virtual void OnInit() override;
			virtual void OnUpdate(Clock clock) override;
			virtual void OnRelease() override;

		private:
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
			std::shared_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<pawn::GraphicsBuffer> m_VertexBuffer;

			std::shared_ptr<DirectX11VertexShader> m_VertexShader;
			std::shared_ptr<DirectX11PixelShader> m_PixelShader;
		
			Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	};
	
}

#endif
