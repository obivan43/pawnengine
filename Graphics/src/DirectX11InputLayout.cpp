#include "pch.h"
#include "DirectX11InputLayout.h"
#include "DirectX11Debug.h"
#include "DirectX11Context.h"

namespace pawn {

	DXGI_FORMAT DirectX11InputLayout::GraphicsInputElementTypeToDX11Type(GraphicsInputElementType type) {
		switch (type) {
			case GraphicsInputElementType::Float:    return DXGI_FORMAT_R32_FLOAT;
			case GraphicsInputElementType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
			case GraphicsInputElementType::Float3:   return DXGI_FORMAT_R32G32B32_FLOAT;
			case GraphicsInputElementType::Float4:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case GraphicsInputElementType::Int:      return DXGI_FORMAT_R32_SINT;
			case GraphicsInputElementType::Int2:     return DXGI_FORMAT_R32G32_SINT;
			case GraphicsInputElementType::Int3:     return DXGI_FORMAT_R32G32B32_SINT;
			case GraphicsInputElementType::Int4:     return DXGI_FORMAT_R32G32B32A32_SINT;
		}

		return DXGI_FORMAT_UNKNOWN;
	}

	void DirectX11InputLayout::Init(std::shared_ptr<GraphicsContext>& context, ID3DBlob* blob, const std::initializer_list<GraphicsInputElement>& elements) {
		DirectX11InputLayout::Init(context, elements);

		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11Device* device = directX11Context->GetDevice();

		DirectX11Call(device->CreateInputLayout(
			m_InputDescription,
			static_cast<UINT>(elements.size()),
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			&m_InputLayout
		))

		delete[] m_InputDescription;
	}
	
	void DirectX11InputLayout::Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements) {
		GraphicsInputLayout::Init(context, elements);
		
		m_InputDescription = new D3D11_INPUT_ELEMENT_DESC[elements.size()];
		uint32_t inputSlot = 0;
		for(const auto& element : elements) {
			D3D11_INPUT_ELEMENT_DESC desription = {
				element.Name.c_str(),
				0,
				GraphicsInputElementTypeToDX11Type(element.Type),
				inputSlot,
				element.Offset,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			};

			m_InputDescription[inputSlot] = desription;
			
			++inputSlot;
		}
	}
	
	void DirectX11InputLayout::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();
		deviceContext->IASetInputLayout(m_InputLayout.Get());
	}
	
}