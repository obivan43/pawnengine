#pragma once

#include "Layer.h"
#include "CameraInputHandler.h"

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
			std::shared_ptr<pawn::GraphicsBuffer> m_IndexBuffer;
			std::shared_ptr<pawn::GraphicsBuffer> m_Transformation;
			std::shared_ptr<pawn::GraphicsBuffer> m_ViewProjection;
			std::shared_ptr<pawn::GraphicsTexture2D> m_Texture;

			std::shared_ptr<GraphicsShader> m_Shader;
			std::shared_ptr<GraphicsInputLayout> m_InputLayout;
			std::shared_ptr<GraphicsRenderer> m_GraphicsRenderer;

			std::wstring m_VertexShaderPath;
			std::wstring m_PixelShaderPath;

			Transformation m_TransformationMatrix;
		
			Camera m_Camera;
			CameraInputHandler m_CameraMovement;
			ViewProjection m_ViewProjectionMatrix;
	};
	
}
