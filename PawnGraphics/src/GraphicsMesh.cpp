#include "pch.h"
#include "GraphicsMesh.h"

namespace pawn {

	GraphicsMesh::GraphicsMesh() {}

	GraphicsMesh::GraphicsMesh(const std::shared_ptr<pawn::GraphicsBuffer>& vertexBuffer, std::shared_ptr<pawn::GraphicsBuffer>& indexBuffer, std::shared_ptr<GraphicsInputLayout>& inputLayout)
	: m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer), m_InputLayout(inputLayout) {}

	void GraphicsMesh::Bind(std::shared_ptr<GraphicsContext>& context) {
		if(m_VertexBuffer != nullptr && m_IndexBuffer != nullptr) {
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

}
