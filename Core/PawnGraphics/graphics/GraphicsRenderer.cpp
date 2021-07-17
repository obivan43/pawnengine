#include "GraphicsRenderer.h"
#include "GraphicsContext.h"
#include "GraphicsBuffer.h"
#include "directx/DirectX11Renderer.h"

namespace pawn {

	namespace graphics {

		void GraphicsRenderer::Draw(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& buffer) { UNUSED(buffer) }

		void GraphicsRenderer::DrawIndexed(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& IndexBuffer) { UNUSED(IndexBuffer) }

		std::shared_ptr<GraphicsRenderer> GraphicsRenderer::Create() {
#ifdef PAWN_DIRECTX11
			return std::shared_ptr<GraphicsRenderer>(new DirectX11Renderer());
#else
			return std::shared_ptr<GraphicsRenderer>(new GraphicsRenderer());
#endif
		}

	}
	
}
