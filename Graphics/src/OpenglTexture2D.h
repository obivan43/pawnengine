#pragma once

#include "GraphicsTexture2D.h"

#ifdef PAWN_OPENGL

namespace pawn {
	
	class OpenglTexture2D : public GraphicsTexture2D {

		public:
			OpenglTexture2D() = default;
			OpenglTexture2D(const OpenglTexture2D& other) = default;
			OpenglTexture2D(OpenglTexture2D&& other) noexcept = default;

			OpenglTexture2D& operator=(const OpenglTexture2D& other) = default;
			OpenglTexture2D& operator=(OpenglTexture2D&& other) noexcept = default;

			~OpenglTexture2D() override;

			void Init(
				std::shared_ptr<GraphicsContext>& context,
				const void* data,
				int32_t width,
				int32_t height,
				int32_t bitsPerPixel,
				const GraphicsTextureParams& params
			) override;
		
			void Bind(std::shared_ptr<GraphicsContext>& context) override;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;

			void* GetTexture() override { return &m_Texture; }

		private:
			static uint32_t TextureWrapToOpengl(GraphicsTextureWrap wrap);
	
		private:
			uint32_t m_Texture;
	};

}

#endif