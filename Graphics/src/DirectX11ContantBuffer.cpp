#include "pch.h"
#include "DirectX11ContantBuffer.h"
#include "DirectX11Context.h"

#include <d3d11.h>

#ifdef PAWN_DIRECTX11

namespace pawn {

	DirectX11ContantBuffer::DirectX11ContantBuffer() : DirectX11BufferBase(GraphicsBufferEnum::ConstantBuffer) {}

	void DirectX11ContantBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->VSSetConstantBuffers(0, 1, m_Buffer.GetAddressOf());
	}

	void DirectX11ContantBuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}

	void DirectX11ContantBuffer::Init(
		std::shared_ptr<GraphicsContext>& context,
		void* data,
		uint32_t numVertices,
		uint32_t sizeofBufferDataType,
		GraphicsBufferUsageTypeEnum type
	) {
		DirectX11BufferBase::Init(context, data, numVertices, sizeofBufferDataType, type);
	}
}

#endif
