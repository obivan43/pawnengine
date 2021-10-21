#include "DirectX11VertexBuffer.h"

#include "PawnGraphics/graphics/directx/DirectX11Context.h"
#include "PawnUtils/utils/codetools/Macros.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn::graphics {

	DirectX11VertexBuffer::DirectX11VertexBuffer() : DirectX11BufferBase(GraphicsBufferEnum::VertexBuffer), m_LastBoundIndex(0) {}

	void DirectX11VertexBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		const UINT offset{ 0 };
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->IASetVertexBuffers(0, 1, m_Buffer.GetAddressOf(), &m_Stride, &offset);
		m_LastBoundIndex = 0;
	}

	void DirectX11VertexBuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		const UINT offset{ 0 };
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->IASetVertexBuffers(index, 1, m_Buffer.GetAddressOf(), &m_Stride, &offset);
		m_LastBoundIndex = index;
	}

	void DirectX11VertexBuffer::Unbind(std::shared_ptr<GraphicsContext>& context) {
		const UINT offset{ 0 };
		const UINT stride{ 0 };
		DirectX11Context* directX11Context = context->As<DirectX11Context>();

		Microsoft::WRL::ComPtr<ID3D11Buffer> nullBuffer;
		directX11Context->GetDeviceContext()->IASetVertexBuffers(m_LastBoundIndex, 1, nullBuffer.GetAddressOf(), &stride, &offset);
	}
}

#endif
