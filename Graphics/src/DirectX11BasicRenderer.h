#pragma once

#include "GraphicsRenderer.h"

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	class DirectX11BasicRenderer : public GraphicsRenderer {
		
		public:
			DirectX11BasicRenderer(const std::shared_ptr<GraphicsContext>& context);
			DirectX11BasicRenderer(const DirectX11BasicRenderer& other) = default;
			DirectX11BasicRenderer(DirectX11BasicRenderer&& other) noexcept = default;

			DirectX11BasicRenderer& operator=(const DirectX11BasicRenderer& other) = default;
			DirectX11BasicRenderer& operator=(DirectX11BasicRenderer&& other) noexcept = default;

			void Draw(const std::shared_ptr<GraphicsBuffer>& buffer) override;
			void DrawIndexed(const std::shared_ptr<GraphicsBuffer>& IndexBuffer) override;
	};
	
}

#endif