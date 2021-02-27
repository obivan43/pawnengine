﻿#include "pch.h"
#include "GraphicsTexture2D.h"
#include "OpenglTexture2D.h"
#include "DirectX11Texture2D.h"

namespace pawn {

	GraphicsTexture2D::GraphicsTexture2D() :
	m_Width(0),
	m_Height(0),
	m_Params({ GraphicsTextureWrap::CLAMP, GraphicsTextureFilter::LINEAR, GraphicsTextureFormat::RGB }) {}
	
	void GraphicsTexture2D::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}

	void GraphicsTexture2D::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(context)
		UNUSED(index)
	}

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
#elif PAWN_OPENGL
		return std::shared_ptr<GraphicsTexture2D>(new OpenglTexture2D());
#else
		return std::shared_ptr<GraphicsTexture2D>(new GraphicsTexture2D());
#endif
	}
	
}