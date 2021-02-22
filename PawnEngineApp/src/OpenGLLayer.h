#pragma once

#include "Layer.h"

#ifdef PAWN_OPENGL

namespace pawn {
	
	class OpenGLLayer : public Layer {

		public:
			OpenGLLayer() = default;
			OpenGLLayer(const OpenGLLayer& other) = delete;
			OpenGLLayer(OpenGLLayer&& other) noexcept = default;

			OpenGLLayer& operator=(const OpenGLLayer& other) = delete;
			OpenGLLayer& operator=(OpenGLLayer&& other) noexcept = delete;

			void OnInit() override;
			void OnUpdate(Clock clock) override;
			void OnRelease() override;

			void HandleEvent(Event& e) override;

		private:
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
			std::shared_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<pawn::GraphicsBuffer> m_VertexBuffer;

			std::shared_ptr<GraphicsInputLayout> m_InputLayout;
			std::shared_ptr<GraphicsRenderer> m_GraphicsRenderer;

			std::shared_ptr<OpenglShader> m_Shader;
	};
	
}

#endif
