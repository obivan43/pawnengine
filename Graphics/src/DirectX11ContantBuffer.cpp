#include "pch.h"
#include "DirectX11ContantBuffer.h"
#include "DirectX11Debug.h"
#include "DirectX11Context.h"

#ifdef PAWN_DIRECTX11

namespace pawn {

	DirectX11ContantBuffer::DirectX11ContantBuffer()
		: m_BufferSize(0), m_Stride(0) {
		m_GraphicsBufferType = GraphicsBufferEnum::ConstantBuffer;
	}

	void DirectX11ContantBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->VSSetConstantBuffers(0, 1, m_Buffer.GetAddressOf());
	}

	void DirectX11ContantBuffer::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11Device* device = directX11Context->GetDevice();

		m_BufferSize = numVertices;
		m_Stride = stride;

		D3D11_BUFFER_DESC bufferDescription = {};
		bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		bufferDescription.ByteWidth = stride * numVertices;
		bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDescription.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData = {};
		vertexBufferData.pSysMem = data;

		DirectX11Call(device->CreateBuffer(&bufferDescription, &vertexBufferData, &m_Buffer))

		spdlog::get("console")->info("Constant buffer created");
	}
}

#endif
