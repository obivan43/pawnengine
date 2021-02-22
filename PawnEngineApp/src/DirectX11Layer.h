﻿#pragma once

#include "Layer.h"

namespace pawn {
	
	class DirectX11Layer : public Layer {
		
		public:
			DirectX11Layer() = default;
			DirectX11Layer(const DirectX11Layer& other) = delete;
			DirectX11Layer(DirectX11Layer&& other) noexcept = default;

			DirectX11Layer& operator=(const DirectX11Layer& other) = delete;
			DirectX11Layer& operator=(DirectX11Layer&& other) noexcept = delete;
		
			void OnInit() override;
			void OnUpdate(Clock clock) override;
			void OnRelease() override;

		private:
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
			std::shared_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<pawn::GraphicsBuffer> m_VertexBuffer;

			std::shared_ptr<GraphicsInputLayout> m_InputLayout;
			std::shared_ptr<GraphicsRenderer> m_GraphicsRenderer;

#ifdef PAWN_DIRECTX11
			std::shared_ptr<DirectX11Shader> m_Shader;
#else
			std::shared_ptr<OpenglShader> m_Shader;
#endif
	};
	
}
