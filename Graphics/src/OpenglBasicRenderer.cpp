#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglBasicRenderer.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglBasicRenderer::OpenglBasicRenderer(const std::shared_ptr<GraphicsContext>& context) : GraphicsRenderer(context) {}

	void OpenglBasicRenderer::Draw(const std::shared_ptr<GraphicsBuffer>& buffer) {
		OpenglCall(glDrawArrays(GL_TRIANGLES, 0, buffer->GetBufferSize()))
	}

	void OpenglBasicRenderer::DrawIndexed(const std::shared_ptr<GraphicsBuffer>& IndexBuffer) {
		OpenglCall(glDrawElements(GL_TRIANGLES, IndexBuffer->GetBufferSize(), GL_UNSIGNED_SHORT, nullptr))
	}
}

#endif
