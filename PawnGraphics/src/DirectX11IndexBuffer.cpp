#include "pch.h"
#include "DirectX11IndexBuffer.h"
#include "DirectX11Context.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	DirectX11IndexBuffer::DirectX11IndexBuffer() : DirectX11BufferBase(GraphicsBufferEnum::IndexBuffer) {}

	void DirectX11IndexBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		const UINT offset = 0;
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	}

	void DirectX11IndexBuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}
}

#endif