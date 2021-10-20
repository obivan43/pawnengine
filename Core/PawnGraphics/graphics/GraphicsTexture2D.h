#pragma once

#include "GraphicsBindableResource.h"

#include <memory>

namespace pawn::graphics {

	class GraphicsContext;

	enum class GraphicsTextureWrap {
		REPEAT,
		CLAMP,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum class GraphicsTextureFilter {
		LINEAR,
		NEAREST
	};

	enum class GraphicsTextureFormat {
		RGB,
		RGBA
	};

	struct GraphicsTextureParams {
		GraphicsTextureWrap m_WrapMode;
		GraphicsTextureFilter m_FilterMode;
		GraphicsTextureFormat m_Format;
	};

	class GraphicsTexture2D : public GraphicsBindableResource {

		public:
			GraphicsTexture2D();
			GraphicsTexture2D(const GraphicsTexture2D& other) = default;
			GraphicsTexture2D(GraphicsTexture2D&& other) noexcept = default;

			GraphicsTexture2D& operator=(const GraphicsTexture2D& other) = default;
			GraphicsTexture2D& operator=(GraphicsTexture2D&& other) noexcept = default;

			virtual ~GraphicsTexture2D() = default;

			virtual void Init(
				std::shared_ptr<GraphicsContext>& context,
				const void* data,
				int32_t width,
				int32_t height,
				int32_t bitsPerPixel,
				const GraphicsTextureParams& params
			);

			void Bind(std::shared_ptr<GraphicsContext>& context) override;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override;

			virtual void* GetTexture() { return nullptr; }

			static std::shared_ptr<GraphicsTexture2D> Create();

		protected:
			int32_t m_Width;
			int32_t m_Height;
			int32_t m_BitsPerPixel;
			GraphicsTextureParams m_Params;
	};
	
}
