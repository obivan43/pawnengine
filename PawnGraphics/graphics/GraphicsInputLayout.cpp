#include "GraphicsInputLayout.h"
#include "GraphicsContext.h"
#include "directx/DirectX11InputLayout.h"

namespace pawn {

	namespace graphics {

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

			switch (m_Type) {
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
			: m_Name(name), m_Type(type), m_Size(GraphicsInputElementTypeSize(type)), m_Offset(0)
		{}

		GraphicsInputElement::~GraphicsInputElement() {}

		GraphicsInputLayout::GraphicsInputLayout() : m_Stride(0) {}

		GraphicsInputLayout::~GraphicsInputLayout() {}

		void GraphicsInputLayout::Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData) {
			UNUSED(context)
			UNUSED(shaderData)
			UNUSED(elements)
		}

		void GraphicsInputLayout::RecalculateStride() {
			size_t offset{ 0 };
			m_Stride = 0;

			for (auto& element : m_Elements) {
				element.m_Offset = offset;
				offset += element.m_Size;
				m_Stride += element.m_Size;
			}
		}

		void GraphicsInputLayout::Bind(std::shared_ptr<GraphicsContext>& context) { UNUSED(context) }

		void GraphicsInputLayout::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
			UNUSED(context)
			UNUSED(index)
		}

		std::shared_ptr<GraphicsInputLayout> GraphicsInputLayout::Create() {
#ifdef PAWN_DIRECTX11
			return std::shared_ptr<GraphicsInputLayout>(new DirectX11InputLayout());
#else
			return std::shared_ptr<GraphicsInputLayout>(new GraphicsInputLayout());
#endif
		}

	}

}
