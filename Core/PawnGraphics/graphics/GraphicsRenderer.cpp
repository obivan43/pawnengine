﻿#include "GraphicsRenderer.h"

#include "GraphicsBuffer.h"
#include "GraphicsContext.h"

#include "directx/DirectX11Renderer.h"

namespace pawn::graphics {

	void GraphicsRenderer::Draw(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& buffer) { 
		UNUSED(context)
		UNUSED(buffer) 
	}

	void GraphicsRenderer::DrawIndexed(
		std::shared_ptr<GraphicsContext>& context,
		uint32_t indexCount,
		uint32_t startIndex,
		uint32_t vertexLocation
	) { 
		UNUSED(context)
		UNUSED(indexCount)
		UNUSED(startIndex)
		UNUSED(vertexLocation)
	}

	std::shared_ptr<GraphicsRenderer> GraphicsRenderer::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsRenderer>(new DirectX11Renderer());
#else
		return std::shared_ptr<GraphicsRenderer>(new GraphicsRenderer());
#endif
	}
	
}
