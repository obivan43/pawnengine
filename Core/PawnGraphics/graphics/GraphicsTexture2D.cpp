#include "GraphicsTexture2D.h"
#include "GraphicsContext.h"
#include "directx/DirectX11Texture2D.h"

#include "PawnUtils/utils/codetools/Macros.h"

namespace pawn::graphics {

	GraphicsTexture2D::GraphicsTexture2D() :
		m_Width(0),
		m_Height(0),
		m_Params({ GraphicsTextureWrap::CLAMP, GraphicsTextureFilter::LINEAR, GraphicsTextureFormat::RGB })
	{}

	void GraphicsTexture2D::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}

	void GraphicsTexture2D::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(context)
		UNUSED(index)
	}

	void GraphicsTexture2D::Unbind(std::shared_ptr<GraphicsContext>& context) { UNUSED(context) }

	void GraphicsTexture2D::Init(
		std::shared_ptr<GraphicsContext>& context,
		const void* data,
		int32_t width,
		int32_t height,
		int32_t bitsPerPixel,
		const GraphicsTextureParams& params) {
		UNUSED(context)
		UNUSED(data)
		UNUSED(width)
		UNUSED(height)
		UNUSED(bitsPerPixel)
		UNUSED(params)
	}

	std::shared_ptr<GraphicsTexture2D> GraphicsTexture2D::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsTexture2D>(new DirectX11Texture2D());
#else
		return std::shared_ptr<GraphicsTexture2D>(new GraphicsTexture2D());
#endif
	}
	
}
