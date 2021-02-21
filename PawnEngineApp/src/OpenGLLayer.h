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

		private:
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
			std::shared_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
	};
	
}

#endif
