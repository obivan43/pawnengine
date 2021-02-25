#pragma once

#include "GraphicsBindableResource.h"

namespace pawn {
	
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
	
	class GraphicsTexture : public GraphicsBindableResource {

		public:
			GraphicsTexture();
			GraphicsTexture(const GraphicsTexture& other) = default;
			GraphicsTexture(GraphicsTexture&& other) noexcept = default;

			GraphicsTexture& operator=(const GraphicsTexture& other) = default;
			GraphicsTexture& operator=(GraphicsTexture&& other) noexcept = default;
		
			virtual ~GraphicsTexture() = default;

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

			virtual void* GetTexture() { return nullptr; }

		protected:
			int32_t m_Width;
			int32_t m_Height;
			int32_t m_BitsPerPixel;
			GraphicsTextureParams m_Params;
	};
	
}
