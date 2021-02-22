#include "pch.h"
#include "Opengl.h"
#include "OpenglInputLayout.h"

#ifdef PAWN_OPENGL

namespace pawn {

	uint32_t OpenglInputLayout::GraphicsInputElementTypeToOpenglType(GraphicsInputElementType type) {
		switch (type) {
			case GraphicsInputElementType::Float:    return GL_FLOAT;
			case GraphicsInputElementType::Float2:   return GL_FLOAT;
			case GraphicsInputElementType::Float3:   return GL_FLOAT;
			case GraphicsInputElementType::Float4:   return GL_FLOAT;
			case GraphicsInputElementType::Int:      return GL_INT;
			case GraphicsInputElementType::Int2:     return GL_INT;
			case GraphicsInputElementType::Int3:     return GL_INT;
			case GraphicsInputElementType::Int4:     return GL_INT;
		}

		return GL_FLOAT;
	}

	OpenglInputLayout::OpenglInputLayout() : m_InputLayout(0) {}

	OpenglInputLayout::~OpenglInputLayout() {
		glDeleteVertexArrays(1, &m_InputLayout);
	}

	void OpenglInputLayout::Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData) {
		glGenVertexArrays(1, &m_InputLayout);
		glBindVertexArray(m_InputLayout);

		uint32_t inputSlot = 0;
		for (const auto& element : elements) {
			glEnableVertexAttribArray(inputSlot);
			glVertexAttribPointer(
				inputSlot,
				element.ElementCount(),
				GraphicsInputElementTypeToOpenglType(element.Type),
				GL_FALSE,
				GraphicsInputElement::GraphicsInputElementTypeSize(element.Type),
				reinterpret_cast<const void*>(element.Offset)
			);

			++inputSlot;
		}
	}

	void OpenglInputLayout::Bind(std::shared_ptr<GraphicsContext>& context) {
		glBindVertexArray(m_InputLayout);
	}

}

#endif