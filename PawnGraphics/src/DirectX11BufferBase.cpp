#include "DirectX11BufferBase.h"
#include "DirectX11Debug.h"
#include "DirectX11Context.h"

#include "PAwnUtils/utils/logger/Logger.h"

#ifdef PAWN_DIRECTX11

namespace pawn {

	D3D11_BIND_FLAG DirectX11BufferBase::BufferTypeToDirectXBufferType(GraphicsBufferEnum type) {
		switch (type) {
			case GraphicsBufferEnum::VertexBuffer:
				return D3D11_BIND_VERTEX_BUFFER;
			case GraphicsBufferEnum::IndexBuffer:
				return D3D11_BIND_INDEX_BUFFER;
			case GraphicsBufferEnum::ConstantBuffer:
				return D3D11_BIND_CONSTANT_BUFFER;
		}

		return D3D11_BIND_VERTEX_BUFFER;
	}

	const char* DirectX11BufferBase::BufferTypeMessage(GraphicsBufferEnum type) {
		switch (type) {
			case GraphicsBufferEnum::VertexBuffer:
				return "Vertex";
			case GraphicsBufferEnum::IndexBuffer:
				return "Index";
			case GraphicsBufferEnum::ConstantBuffer:
				return "Constant";
		}

		return "";
	}

	D3D11_USAGE DirectX11BufferBase::BufferUsageTypeToDirectXBufferUsageType(GraphicsBufferUsageTypeEnum usageType) {
		switch (usageType) {
			case GraphicsBufferUsageTypeEnum::StaticBuffer:
				return D3D11_USAGE_DEFAULT;
			case GraphicsBufferUsageTypeEnum::DynamicBuffer:
				return D3D11_USAGE_DYNAMIC;
		}
		
		return D3D11_USAGE_DEFAULT;
	}

	DirectX11BufferBase::DirectX11BufferBase(GraphicsBufferEnum type)
		: m_BufferSize(0), m_Stride(0), m_UsageType(GraphicsBufferUsageTypeEnum::StaticBuffer) {
		m_GraphicsBufferType = type;
	}

	void DirectX11BufferBase::Update(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();
		
		switch (m_UsageType) {
			case GraphicsBufferUsageTypeEnum::StaticBuffer: {
				Init(context, data, numVertices, stride, m_UsageType);
			}
			break;

			case GraphicsBufferUsageTypeEnum::DynamicBuffer: {
				D3D11_MAPPED_SUBRESOURCE mapping;
				DirectX11Call(deviceContext->Map(m_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping))
				memcpy(mapping.pData, data, numVertices * stride);
				deviceContext->Unmap(m_Buffer.Get(), 0);
			}
			break;

			default: break;
		}
	}

	void DirectX11BufferBase::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride, GraphicsBufferUsageTypeEnum type) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11Device* device = directX11Context->GetDevice();

		m_BufferSize = numVertices;
		m_Stride = stride;
		m_UsageType = type;

		D3D11_BUFFER_DESC bufferDescription = {};
		bufferDescription.Usage = BufferUsageTypeToDirectXBufferUsageType(type);
		bufferDescription.ByteWidth = stride * numVertices;
		bufferDescription.BindFlags = BufferTypeToDirectXBufferType(m_GraphicsBufferType);
		bufferDescription.CPUAccessFlags = type == GraphicsBufferUsageTypeEnum::StaticBuffer ? 0 : D3D11_CPU_ACCESS_WRITE;
		bufferDescription.MiscFlags = 0;

		if (data != nullptr) {
			D3D11_SUBRESOURCE_DATA resourceData = {};
			resourceData.pSysMem = data;

			DirectX11Call(device->CreateBuffer(&bufferDescription, &resourceData, &m_Buffer))
		}
		else {
			DirectX11Call(device->CreateBuffer(&bufferDescription, nullptr, &m_Buffer))
		}


		CONSOLE_INFO("{} buffer created", BufferTypeMessage(m_GraphicsBufferType))
	}
}

#endif