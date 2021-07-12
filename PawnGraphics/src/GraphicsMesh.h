#pragma once

#include "GraphicsBindableResource.h"
#include "GraphicsBuffer.h"
#include "GraphicsInputLayout.h"

#include <memory>

namespace pawn {

	class GraphicsMesh : public GraphicsBindableResource {

		public:
			GraphicsMesh();
			GraphicsMesh(const std::shared_ptr<pawn::GraphicsBuffer>& vertexBuffer, std::shared_ptr<pawn::GraphicsBuffer>& indexBuffer, std::shared_ptr<GraphicsInputLayout>& inputLayout);
			GraphicsMesh(const GraphicsMesh& other) = default;
			GraphicsMesh(GraphicsMesh&& other) noexcept = default;

			GraphicsMesh& operator=(const GraphicsMesh& other) = default;
			GraphicsMesh& operator=(GraphicsMesh&& other) noexcept = default;

			void Bind(std::shared_ptr<GraphicsContext>& context);
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index);

			void SetVertexBuffer(const std::shared_ptr<pawn::GraphicsBuffer>& vertexBuffer) { m_VertexBuffer = vertexBuffer; }
			void SetIndexBuffer(const std::shared_ptr<pawn::GraphicsBuffer>& indexBuffer) { m_IndexBuffer = indexBuffer; }
			void SetInputLayout(const std::shared_ptr<pawn::GraphicsInputLayout>& inputLayout) { m_InputLayout = inputLayout; }

			const std::shared_ptr<pawn::GraphicsBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
			const std::shared_ptr<pawn::GraphicsBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
			const std::shared_ptr<pawn::GraphicsInputLayout>& GetInputLayout() const { return m_InputLayout; }

		private:
			std::shared_ptr<pawn::GraphicsBuffer> m_VertexBuffer;
			std::shared_ptr<pawn::GraphicsBuffer> m_IndexBuffer;
			std::shared_ptr<pawn::GraphicsInputLayout> m_InputLayout;
	};

}