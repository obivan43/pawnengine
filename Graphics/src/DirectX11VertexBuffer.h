#pragma once

#include "GraphicsBuffer.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {
	
	class DirectX11VertexBuffer : public GraphicsBuffer {
		
		public:
			DirectX11VertexBuffer();

			virtual void Bind(std::shared_ptr<GraphicsContext>& context) override;
			virtual uint32_t GetBufferSize() const override { return m_BufferSize; }
			virtual uint32_t GetStride() const override { return m_Stride; }
		
			void Initialize(ID3D11Device* device, void* data, uint32_t numVertices, uint32_t sizeofBufferDataType);

			ID3D11Buffer* GetBuffer() const { return m_Buffer.Get(); }
	
		private:
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
			uint32_t m_BufferSize;
			uint32_t m_Stride;
	};
	
}

#endif
