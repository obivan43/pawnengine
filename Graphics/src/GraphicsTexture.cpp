#include "pch.h"
#include "GraphicsTexture.h"

namespace pawn {

	GraphicsTexture::GraphicsTexture() :
	m_Width(0),
	m_Height(0),
	m_Params({ GraphicsTextureWrap::CLAMP, GraphicsTextureFilter::LINEAR, GraphicsTextureFormat::RGB }) {}
	
	void GraphicsTexture::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}

	void GraphicsTexture::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(context)
		UNUSED(index)
	}

	void GraphicsTexture::Init(
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
	
}