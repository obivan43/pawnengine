#include "pch.h"
#include "GraphicsInputLayout.h"

namespace pawn {

	uint32_t GraphicsInputElement::GraphicsInputElementTypeSize(GraphicsInputElementType type) {

		switch (type) {
			case GraphicsInputElementType::Float:    return 4;
			case GraphicsInputElementType::Float2:   return 4 * 2;
			case GraphicsInputElementType::Float3:   return 4 * 3;
			case GraphicsInputElementType::Float4:   return 4 * 4;
			case GraphicsInputElementType::Int:      return 4;
			case GraphicsInputElementType::Int2:     return 4 * 2;
			case GraphicsInputElementType::Int3:     return 4 * 3;
			case GraphicsInputElementType::Int4:     return 4 * 4;
		}

		return 0;
	}

	uint32_t GraphicsInputElement::ElementCount() const {
		
		switch (Type) {
			case GraphicsInputElementType::Float:    return 1;
			case GraphicsInputElementType::Float2:   return 2;
			case GraphicsInputElementType::Float3:   return 3;
			case GraphicsInputElementType::Float4:   return 4;
			case GraphicsInputElementType::Int:      return 1;
			case GraphicsInputElementType::Int2:     return 2;
			case GraphicsInputElementType::Int3:     return 3;
			case GraphicsInputElementType::Int4:     return 4;
		}

		return 0;
	}
	
	GraphicsInputElement::GraphicsInputElement(const std::string& name, GraphicsInputElementType type)
	: Name(name), Type(type), Size(GraphicsInputElementTypeSize(type)), Offset(0)
	{}

	GraphicsInputLayout::GraphicsInputLayout() : m_Stride(0) {}

	void GraphicsInputLayout::Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData) {
		UNUSED(context)
		UNUSED(shaderData)
		
		m_Elements = elements;
		RecalculateStride();
	}

	void GraphicsInputLayout::RecalculateStride() {
		uint32_t offset = 0;
		m_Stride = 0;

		for (auto& element : m_Elements) {
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}
	
	void GraphicsInputLayout::Bind(std::shared_ptr<GraphicsContext>& context) { UNUSED(context) }

	void GraphicsInputLayout::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(context)
		UNUSED(index)
	}
	
}
