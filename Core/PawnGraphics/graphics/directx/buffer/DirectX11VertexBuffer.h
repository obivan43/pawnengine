#pragma once

#include "DirectX11BufferBase.h"

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

	class DirectX11VertexBuffer final : public DirectX11BufferBase {

		public:
			DirectX11VertexBuffer();
			DirectX11VertexBuffer(const DirectX11VertexBuffer& other) = default;
			DirectX11VertexBuffer(DirectX11VertexBuffer && other) noexcept = default;

			DirectX11VertexBuffer& operator=(const DirectX11VertexBuffer & other) = default;
			DirectX11VertexBuffer& operator=(DirectX11VertexBuffer && other) noexcept = default;

			void Bind(std::shared_ptr<GraphicsContext>&context) override final;
			void Bind(std::shared_ptr<GraphicsContext>&context, uint32_t index) override final;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override final;

		private:
			uint32_t m_LastBoundIndex;
	};
	
}

#endif
