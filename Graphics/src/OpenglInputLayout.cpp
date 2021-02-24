#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
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
		OpenglCall(glDeleteVertexArrays(1, &m_InputLayout))
	}

	void OpenglInputLayout::Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData) {
		GraphicsInputLayout::Init(context, elements, shaderData);

		OpenglCall(glGenVertexArrays(1, &m_InputLayout))
		OpenglCall(glBindVertexArray(m_InputLayout))

		uint32_t inputSlot = 0;
		for (const auto& element : m_Elements) {
			OpenglCall(glEnableVertexAttribArray(inputSlot))
			OpenglCall(glVertexAttribPointer(
				inputSlot,
				element.ElementCount(),
				GraphicsInputElementTypeToOpenglType(element.Type),
				GL_FALSE,
				m_Stride,
				reinterpret_cast<const void*>(element.Offset)
			))

			++inputSlot;
		}

		spdlog::get("console")->info("Input layout created");
	}

	void OpenglInputLayout::Bind(std::shared_ptr<GraphicsContext>& context) {
		OpenglCall(glBindVertexArray(m_InputLayout))
	}

	void OpenglInputLayout::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}

}

#endif