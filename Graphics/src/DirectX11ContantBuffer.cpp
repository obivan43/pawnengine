#include "pch.h"
#include "DirectX11ContantBuffer.h"
#include "DirectX11Context.h"

#include <d3d11.h>

#ifdef PAWN_DIRECTX11

namespace pawn {

	DirectX11ContantBuffer::DirectX11ContantBuffer() : DirectX11BufferBase(GraphicsBufferEnum::ConstantBuffer) {}

	void DirectX11ContantBuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->VSSetConstantBuffers(index, 1, m_Buffer.GetAddressOf());
	}
	
	void DirectX11ContantBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->VSSetConstantBuffers(m_BindingIndex, 1, m_Buffer.GetAddressOf());
	}

	void DirectX11ContantBuffer::InitLocation(
		std::shared_ptr<GraphicsContext>& context,
		std::shared_ptr<GraphicsShader>& shader,
		const std::string& name,
		uint32_t index
	) {
		m_BindingIndex = index;
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
