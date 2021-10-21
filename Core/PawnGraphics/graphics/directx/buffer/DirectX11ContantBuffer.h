﻿#pragma once

#include "DirectX11BufferBase.h"

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

	class DirectX11ContantBuffer final : public DirectX11BufferBase {

		public:
			DirectX11ContantBuffer();
			DirectX11ContantBuffer(const DirectX11ContantBuffer& other) = default;
			DirectX11ContantBuffer(DirectX11ContantBuffer&& other) noexcept = default;

			DirectX11ContantBuffer& operator=(const DirectX11ContantBuffer& other) = default;
			DirectX11ContantBuffer& operator=(DirectX11ContantBuffer&& other) noexcept = default;

			void Init(
				std::shared_ptr<GraphicsContext>& context,
				void* data,
				uint32_t numVertices,
				uint32_t sizeofBufferDataType,
				GraphicsBufferUsageTypeEnum type = GraphicsBufferUsageTypeEnum::DynamicBuffer
			) override final;

			void Bind(std::shared_ptr<GraphicsContext>& context) override final;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override final;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override final;

		private:
			uint32_t m_LastBoundIndex;
	};

}

#endif
