#pragma once

#include "GraphicsBuffer.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	class DirectX11ContantBuffer : public GraphicsBuffer {

	public:
		DirectX11ContantBuffer();

		void Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t sizeofBufferDataType) override;
		void Bind(std::shared_ptr<GraphicsContext>& context) override;

		void* GetBuffer() const override { return m_Buffer.Get(); }
		uint32_t GetBufferSize() const override { return m_BufferSize; }
		uint32_t GetStride() const override { return m_Stride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
		uint32_t m_BufferSize;
		uint32_t m_Stride;
	};

}

#endif
