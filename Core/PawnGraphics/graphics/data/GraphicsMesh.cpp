#include "GraphicsMesh.h"

#include "PawnUtils/utils/codetools/Macros.h"
#include "PawnUtils/utils/logger/Logger.h"

namespace pawn::graphics {

	GraphicsMesh::GraphicsMesh() {}

	GraphicsMesh::GraphicsMesh(const std::shared_ptr<GraphicsBuffer>& vertexBuffer, std::shared_ptr<GraphicsBuffer>& indexBuffer, std::shared_ptr<GraphicsInputLayout>& inputLayout)
		: m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer), m_InputLayout(inputLayout) {}

	void GraphicsMesh::Bind(std::shared_ptr<GraphicsContext>& context) {
		if (m_VertexBuffer != nullptr && m_IndexBuffer != nullptr) {
			m_VertexBuffer->Bind(context);
			m_IndexBuffer->Bind(context);
			m_InputLayout->Bind(context);
			return;
		}

		CONSOLE_WARN("Bind call on empty mesh")
	}

	void GraphicsMesh::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index);
		Bind(context);
	}

	void GraphicsMesh::Unbind(std::shared_ptr<GraphicsContext>& context) {
		if (m_VertexBuffer != nullptr && m_IndexBuffer != nullptr) {
			m_VertexBuffer->Unbind(context);
			m_IndexBuffer->Unbind(context);
			m_InputLayout->Unbind(context);
			return;
		}

		CONSOLE_WARN("Unbind call on empty mesh")
	}
}
