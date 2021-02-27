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

			void HandleEvent(Event& e) override;

			void OnKeyboardInput();
	
		private:
			Camera m_Camera;
		
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
			std::shared_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<pawn::GraphicsBuffer> m_VertexBuffer;
			std::shared_ptr<pawn::GraphicsBuffer> m_IndexBuffer;
			std::shared_ptr<pawn::GraphicsBuffer> m_Transformation;
			std::shared_ptr<pawn::GraphicsBuffer> m_ViewProjection;
			std::shared_ptr<pawn::GraphicsTexture> m_Texture;
			
			std::shared_ptr<GraphicsInputLayout> m_InputLayout;
			std::shared_ptr<GraphicsRenderer> m_GraphicsRenderer;

			std::shared_ptr<GraphicsShader> m_Shader;

			ViewProjection m_viewProjectionMatrix;
		
			std::wstring m_VertexShaderPath;
			std::wstring m_PixelShaderPath;
	};
	
}
