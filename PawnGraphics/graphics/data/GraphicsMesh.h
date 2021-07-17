#pragma once

#include "PawnGraphics/graphics/GraphicsBindableResource.h"
#include "PawnGraphics/graphics/GraphicsBuffer.h"
#include "PawnGraphics/graphics/GraphicsInputLayout.h"

#include <memory>

namespace pawn {

	class GraphicsMesh : public GraphicsBindableResource {

		public:
			GraphicsMesh();
			GraphicsMesh(const std::shared_ptr<GraphicsBuffer>& vertexBuffer, std::shared_ptr<GraphicsBuffer>& indexBuffer, std::shared_ptr<GraphicsInputLayout>& inputLayout);
			GraphicsMesh(const GraphicsMesh& other) = default;
			GraphicsMesh(GraphicsMesh&& other) noexcept = default;

			GraphicsMesh& operator=(const GraphicsMesh& other) = default;
			GraphicsMesh& operator=(GraphicsMesh&& other) noexcept = default;

			void Bind(std::shared_ptr<GraphicsContext>& context);
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index);

			void SetVertexBuffer(const std::shared_ptr<GraphicsBuffer>& vertexBuffer) { m_VertexBuffer = vertexBuffer; }
			void SetIndexBuffer(const std::shared_ptr<GraphicsBuffer>& indexBuffer) { m_IndexBuffer = indexBuffer; }
			void SetInputLayout(const std::shared_ptr<GraphicsInputLayout>& inputLayout) { m_InputLayout = inputLayout; }

			const std::shared_ptr<GraphicsBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
			const std::shared_ptr<GraphicsBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
			const std::shared_ptr<GraphicsInputLayout>& GetInputLayout() const { return m_InputLayout; }

		private:
			std::shared_ptr<GraphicsBuffer> m_VertexBuffer;
			std::shared_ptr<GraphicsBuffer> m_IndexBuffer;
			std::shared_ptr<GraphicsInputLayout> m_InputLayout;
	};

}