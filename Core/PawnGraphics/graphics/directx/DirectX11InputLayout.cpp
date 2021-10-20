#include "DirectX11InputLayout.h"
#include "DirectX11Context.h"

#include "PawnGraphics/graphics/GraphicsInputLayout.h"
#include "PawnGraphics/graphics/directx/debug/DirectX11Debug.h"

#include "PawnUtils/utils/codetools/Macros.h"
#include "PawnUtils/utils/logger/Logger.h"

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

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

	void DirectX11InputLayout::Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData) {
		GraphicsInputLayout::Init(context, elements, shaderData);
		m_Elements = elements;
		RecalculateStride();

		D3D11_INPUT_ELEMENT_DESC* inputDescription = new D3D11_INPUT_ELEMENT_DESC[m_Elements.size()];
		uint32_t inputSlot{ 0 };
		for (auto& element : m_Elements) {
			D3D11_INPUT_ELEMENT_DESC description = {
				element.m_Name.c_str(),
				0,
				GraphicsInputElementTypeToDX11Type(element.m_Type),
				0,
				static_cast<uint32_t>(element.m_Offset),
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			};

			inputDescription[inputSlot] = description;

			++inputSlot;
		}

		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11Device* device = directX11Context->GetDevice();

		ID3DBlob* blob = static_cast<ID3DBlob*>(shaderData);

		DirectX11Call(device->CreateInputLayout(
			inputDescription,
			static_cast<UINT>(m_Elements.size()),
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			&m_InputLayout
		))

		delete[] inputDescription;

		CONSOLE_INFO("Input layout created")
	}

	void DirectX11InputLayout::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();
		deviceContext->IASetInputLayout(m_InputLayout.Get());
	}

	void DirectX11InputLayout::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}

	void DirectX11InputLayout::Unbind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		ID3D11DeviceContext* deviceContext = directX11Context->GetDeviceContext();

		Microsoft::WRL::ComPtr<ID3D11InputLayout> nullInputLayout;
		deviceContext->IASetInputLayout(nullInputLayout.Get());
	}

}

#endif
