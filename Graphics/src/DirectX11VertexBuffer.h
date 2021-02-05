#pragma once

#include "GraphicsBuffer.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {
	
	class DirectX11VertexBuffer : public GraphicsBuffer {
		
		public:
			DirectX11VertexBuffer();

			~DirectX11VertexBuffer() override;

			void Bind(std::shared_ptr<GraphicsContext>& context) override;
		
			void Initialize(ID3D11Device* device, void* data, uint32_t numVertices, uint32_t sizeofBufferDataType);

			ID3D11Buffer* GetBuffer() const { return m_buffer; }
			uint32_t GetBufferSize() const { return m_BufferSize; }
			uint32_t GetStride() const { return m_Stride; }
	
		private:
			ID3D11Buffer* m_buffer;
			uint32_t m_BufferSize;
			uint32_t m_Stride;
	};
	
}

#endif
