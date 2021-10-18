#pragma once

#include "PawnGraphics/graphics/GraphicsRenderer.h"

#include <memory>

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	namespace graphics {

		class DirectX11Renderer : public GraphicsRenderer {

			public:
				DirectX11Renderer() = default;
				DirectX11Renderer(const DirectX11Renderer& other) = default;
				DirectX11Renderer(DirectX11Renderer&& other) noexcept = default;

				DirectX11Renderer& operator=(const DirectX11Renderer& other) = default;
				DirectX11Renderer& operator=(DirectX11Renderer&& other) noexcept = default;

				void Draw(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsBuffer>& buffer) override;
				void DrawIndexed(
					std::shared_ptr<GraphicsContext>& context,
					const std::shared_ptr<GraphicsBuffer>& IndexBuffer,
					uint32_t startIndex = 0,
					uint32_t vertexLocation = 0
				) override;
		};

	}

}

#endif
