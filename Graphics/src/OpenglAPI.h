#pragma once

#include "GraphicsAPI.h"

#ifdef PAWN_OPENGL

#include <gl/GL.h>

namespace pawn {

	class OpenglContext;
	
	class OpenglAPI : public GraphicsAPI {
		
		public:
			OpenglAPI();
			OpenglAPI(const OpenglAPI& other) = default;
			OpenglAPI(OpenglAPI&& other) noexcept = default;

			OpenglAPI& operator=(const OpenglAPI& other) = default;
			OpenglAPI& operator=(OpenglAPI&& other) noexcept = default;

			~OpenglAPI() = default;

			void SetContext(std::shared_ptr<GraphicsContext>& context) override final;

			void SetClearColor(float r, float g, float b) override;
			void Clear() override final;
			void SetViewport(uint32_t width, uint32_t height);
	
		private:
			OpenglContext* m_OpenglContext;
	};
	
}

#endif
