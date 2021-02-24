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
	
	class GraphicsTexture : public GraphicsBindableResource {

		public:
			GraphicsTexture();
			GraphicsTexture(const GraphicsTexture& other) = default;
			GraphicsTexture(GraphicsTexture&& other) noexcept = default;

			GraphicsTexture& operator=(const GraphicsTexture& other) = default;
			GraphicsTexture& operator=(GraphicsTexture&& other) noexcept = default;
		
			virtual ~GraphicsTexture() = default;

			void Bind(std::shared_ptr<GraphicsContext>& context) override;

		protected:
			int32_t m_Width;
			int32_t m_Height;
			GraphicsTextureWrap m_WrapMode;
			GraphicsTextureFilter m_FilterMode;
			GraphicsTextureFormat m_Format;
	};
	
}
