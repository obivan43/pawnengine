#include "pch.h"
#include "GraphicsRenderer.h"
#include "OpenglBasicRenderer.h"
#include "DirectX11BasicRenderer.h"

namespace pawn {
	
	GraphicsRenderer::GraphicsRenderer(const std::shared_ptr<GraphicsContext>& context) : m_ContextCache(context) {}

	void GraphicsRenderer::Draw(const std::shared_ptr<GraphicsBuffer>& buffer) { UNUSED(buffer) }

	void GraphicsRenderer::DrawIndexed(const std::shared_ptr<GraphicsBuffer>& IndexBuffer) { UNUSED(IndexBuffer) }

	std::shared_ptr<GraphicsRenderer> GraphicsRenderer::Create(std::shared_ptr<GraphicsContext>& context) {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsRenderer>(new DirectX11BasicRenderer(context));
#elif PAWN_OPENGL
		return std::shared_ptr<GraphicsRenderer>(new OpenglBasicRenderer(context));
#else
		return std::shared_ptr<GraphicsRenderer>(new GraphicsRenderer(context));
#endif
	}
	
}
