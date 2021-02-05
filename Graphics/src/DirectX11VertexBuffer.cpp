﻿#include "pch.h"
#include "DirectX11VertexBuffer.h"
#include "DirectX11Debug.h"
#include "DirectX11Context.h"

#ifdef PAWN_DIRECTX11

namespace pawn {

	DirectX11VertexBuffer::DirectX11VertexBuffer()
	: m_buffer(nullptr), m_BufferSize(0), m_Stride(0) {
		m_graphicsBufferType = GraphicsBufferEnum::VertexBuffer;
	}

	DirectX11VertexBuffer::~DirectX11VertexBuffer() {
		if(m_buffer != nullptr) {
			m_buffer->Release();
		}
	}

	void DirectX11VertexBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		const UINT offset = 0;
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_buffer, &m_Stride, &offset);
	}

	void DirectX11VertexBuffer::Initialize(ID3D11Device* device, void* data, uint32_t numVertices, uint32_t stride) {
		m_BufferSize = numVertices;
		m_Stride = stride;

		D3D11_BUFFER_DESC bufferDescription = {};
		bufferDescription.Usage = D3D11_USAGE_DEFAULT;
		bufferDescription.ByteWidth = stride * numVertices;
		bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDescription.CPUAccessFlags = 0;
		bufferDescription.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData = {};
		vertexBufferData.pSysMem = data;

		DirectX11Call(device->CreateBuffer(&bufferDescription, &vertexBufferData, &m_buffer))
	}
}

#endif