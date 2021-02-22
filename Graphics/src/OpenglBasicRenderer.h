#pragma once

#include "GraphicsRenderer.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglBasicRenderer : public GraphicsRenderer {

	public:
		OpenglBasicRenderer(const std::shared_ptr<GraphicsContext>& context);
		OpenglBasicRenderer(const OpenglBasicRenderer& other) = default;
		OpenglBasicRenderer(OpenglBasicRenderer&& other) noexcept = default;

		OpenglBasicRenderer& operator=(const OpenglBasicRenderer& other) = default;
		OpenglBasicRenderer& operator=(OpenglBasicRenderer&& other) noexcept = default;

		~OpenglBasicRenderer() = default;

		void Draw(const std::shared_ptr<GraphicsBuffer>& buffer) override;
	};

}

#endif