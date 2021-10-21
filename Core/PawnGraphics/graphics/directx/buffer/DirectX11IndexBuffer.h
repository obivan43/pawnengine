#pragma once

#include "DirectX11BufferBase.h"

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

	class DirectX11IndexBuffer final : public DirectX11BufferBase {

		public:
			DirectX11IndexBuffer();
			DirectX11IndexBuffer(const DirectX11IndexBuffer& other) = default;
			DirectX11IndexBuffer(DirectX11IndexBuffer && other) noexcept = default;

			DirectX11IndexBuffer& operator=(const DirectX11IndexBuffer & other) = default;
			DirectX11IndexBuffer& operator=(DirectX11IndexBuffer && other) noexcept = default;

			void Bind(std::shared_ptr<GraphicsContext>&context) override final;
			void Bind(std::shared_ptr<GraphicsContext>&context, uint32_t index) override final;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override final;
	};

}

#endif
