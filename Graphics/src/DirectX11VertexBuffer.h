#pragma once

#include "DirectX11BufferBase.h"

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	class DirectX11VertexBuffer : public DirectX11BufferBase {
		
		public:
			DirectX11VertexBuffer();

			void Bind(std::shared_ptr<GraphicsContext>& context) override;
	};
	
}

#endif
