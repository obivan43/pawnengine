#include "pch.h"
#include "DirectX11VertexBuffer.h"
#include "DirectX11Context.h"

#include <d3d11.h>

#ifdef PAWN_DIRECTX11

namespace pawn {

	DirectX11VertexBuffer::DirectX11VertexBuffer() : DirectX11BufferBase(GraphicsBufferEnum::VertexBuffer) {}

	void DirectX11VertexBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		const UINT offset = 0;
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->IASetVertexBuffers(0, 1, m_Buffer.GetAddressOf(), &m_Stride, &offset);
	}

	void DirectX11VertexBuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}
}

#endif
