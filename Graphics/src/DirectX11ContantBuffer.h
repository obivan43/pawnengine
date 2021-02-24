#pragma once

#include "DirectX11BufferBase.h"

#ifdef PAWN_DIRECTX11

namespace pawn {

	class DirectX11ContantBuffer : public DirectX11BufferBase {

		public:
			DirectX11ContantBuffer();

			void Init(
				std::shared_ptr<GraphicsContext>& context,
				void* data,
				uint32_t numVertices,
				uint32_t sizeofBufferDataType,
				GraphicsBufferUsageTypeEnum type = GraphicsBufferUsageTypeEnum::DynamicBuffer
			) override;
		
			void Bind(std::shared_ptr<GraphicsContext>& context) override;
	};

}

#endif
