#pragma once

#include "DirectX11BufferBase.h"

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

	class DirectX11VertexBuffer : public DirectX11BufferBase {

		public:
			DirectX11VertexBuffer();
			DirectX11VertexBuffer(const DirectX11VertexBuffer& other) = default;
			DirectX11VertexBuffer(DirectX11VertexBuffer && other) noexcept = default;

			DirectX11VertexBuffer& operator=(const DirectX11VertexBuffer & other) = default;
			DirectX11VertexBuffer& operator=(DirectX11VertexBuffer && other) noexcept = default;

			void Bind(std::shared_ptr<GraphicsContext>&context) override;
			void Bind(std::shared_ptr<GraphicsContext>&context, uint32_t index) override;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override;

		private:
			uint32_t m_LastBoundIndex;
	};
	
}

#endif
