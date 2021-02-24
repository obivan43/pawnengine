#include "pch.h"
#include "GraphicsTexture.h"

namespace pawn {

	GraphicsTexture::GraphicsTexture() :
	m_Width(0),
	m_Height(0),
	m_WrapMode(GraphicsTextureWrap::CLAMP),
	m_FilterMode(GraphicsTextureFilter::LINEAR),
	m_Format(GraphicsTextureFormat::RGB) {}
	
	void GraphicsTexture::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}
	
}