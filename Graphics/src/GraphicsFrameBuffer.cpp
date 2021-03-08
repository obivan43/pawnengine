#include "pch.h"
#include "GraphicsFrameBuffer.h"
#include "OpenglFramebuffer.h"

namespace pawn {

	void GraphicsFrameBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}

	void GraphicsFrameBuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(context)
		UNUSED(index)
	}

	void GraphicsFrameBuffer::Init(std::shared_ptr<GraphicsContext>& context, int32_t width, int32_t height) {
		UNUSED(context)
		UNUSED(width)
		UNUSED(height)
	}

	void GraphicsFrameBuffer::Unbind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}

	std::shared_ptr<pawn::GraphicsFrameBuffer> GraphicsFrameBuffer::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsFrameBuffer>(new GraphicsFrameBuffer());
#elif PAWN_OPENGL
		return std::shared_ptr<GraphicsFrameBuffer>(new OpenglFramebuffer());
#else
		return std::shared_ptr<GraphicsFrameBuffer>(new GraphicsFrameBuffer());
#endif
	}

}
