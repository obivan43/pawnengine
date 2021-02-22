#pragma once

#include "GraphicsContext.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglAPI;
	
	class OpenglContext : public GraphicsContext {

		friend OpenglAPI;
		
		public:
			OpenglContext() = default;
			OpenglContext(const OpenglContext& other) = default;
			OpenglContext(OpenglContext&& other) noexcept = default;
	
			OpenglContext& operator=(const OpenglContext& other) = default;
			OpenglContext& operator=(OpenglContext&& other) noexcept = default;

			virtual ~OpenglContext();
	
			bool Init(const pawn::Window& window) override final;
			void SwapBuffers() override final;
	
		private:
			int32_t m_PixelFormat;
			HDC m_DeviceContext;
			HGLRC m_RenderingContext;
	};
	
}

#endif
