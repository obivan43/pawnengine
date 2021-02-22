#pragma once

#include "Layer.h"

namespace pawn {
	
	class DefaultLayer : public Layer {
		
		public:
			DefaultLayer();
			DefaultLayer(const DefaultLayer& other) = delete;
			DefaultLayer(DefaultLayer&& other) noexcept = default;

			DefaultLayer& operator=(const DefaultLayer& other) = delete;
			DefaultLayer& operator=(DefaultLayer&& other) noexcept = delete;
		
			void OnInit() override;
			void OnUpdate(Clock clock) override;
			void OnRelease() override;

		private:
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
			std::shared_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<pawn::GraphicsBuffer> m_VertexBuffer;

			std::shared_ptr<GraphicsInputLayout> m_InputLayout;
			std::shared_ptr<GraphicsRenderer> m_GraphicsRenderer;

			std::shared_ptr<GraphicsShader> m_Shader;

			std::wstring m_VertexShaderPath;
			std::wstring m_PixelShaderPath;
	};
	
}
