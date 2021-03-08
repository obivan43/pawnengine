#include "pch.h"
#include "Mesh.h"

namespace pawn {

	Mesh::Mesh() {}

	Mesh::Mesh(const std::shared_ptr<pawn::GraphicsBuffer>& vertexBuffer, std::shared_ptr<pawn::GraphicsBuffer>& indexBuffer, std::shared_ptr<GraphicsInputLayout>& inputLayout)
	: m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer), m_InputLayout(inputLayout) {}

	void Mesh::Bind(std::shared_ptr<GraphicsContext>& context) {
		if(m_VertexBuffer != nullptr && m_IndexBuffer != nullptr) {
			m_VertexBuffer->Bind(context);
			m_IndexBuffer->Bind(context);
			m_InputLayout->Bind(context);
			return;
		}

		spdlog::get("console")->error("Bind call on empty mesh");
	}

	void Mesh::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index);
		Bind(context);
	}

}
