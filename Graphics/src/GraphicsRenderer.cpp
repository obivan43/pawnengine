#include "pch.h"
#include "GraphicsRenderer.h"

namespace pawn {
	
	GraphicsRenderer::GraphicsRenderer(const std::shared_ptr<GraphicsContext>& context) : m_ContextCache(context) {}

	void GraphicsRenderer::Draw(const std::shared_ptr<GraphicsBuffer>& buffer) { (void)buffer; }
	
}
