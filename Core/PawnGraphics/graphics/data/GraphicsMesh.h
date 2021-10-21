#pragma once

#include "PawnGraphics/graphics/GraphicsBindableResource.h"
#include "PawnGraphics/graphics/GraphicsBuffer.h"
#include "PawnGraphics/graphics/GraphicsInputLayout.h"

#include <memory>

namespace pawn::graphics {

	class GraphicsMesh : public GraphicsBindableResource {

		public:
			GraphicsMesh();
			GraphicsMesh(
				const std::shared_ptr<GraphicsBuffer>& vertexBuffer,
				std::shared_ptr<GraphicsBuffer>& indexBuffer,
				std::shared_ptr<GraphicsInputLayout>& inputLayout
			);

			GraphicsMesh(const GraphicsMesh& other) = default;
			GraphicsMesh(GraphicsMesh&& other) noexcept = default;

			GraphicsMesh& operator=(const GraphicsMesh& other) = default;
			GraphicsMesh& operator=(GraphicsMesh&& other) noexcept = default;

			void Bind(std::shared_ptr<GraphicsContext>& context);
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index);
			void Unbind(std::shared_ptr<GraphicsContext>& context);

			inline void SetVertexBuffer(const std::shared_ptr<GraphicsBuffer>& vertexBuffer) noexcept { m_VertexBuffer = vertexBuffer; }
			inline void SetIndexBuffer(const std::shared_ptr<GraphicsBuffer>& indexBuffer) noexcept { m_IndexBuffer = indexBuffer; }
			inline void SetInputLayout(const std::shared_ptr<GraphicsInputLayout>& inputLayout) noexcept { m_InputLayout = inputLayout; }

			inline const std::shared_ptr<GraphicsBuffer>& GetVertexBuffer() const noexcept { return m_VertexBuffer; }
			inline const std::shared_ptr<GraphicsBuffer>& GetIndexBuffer() const noexcept { return m_IndexBuffer; }
			inline const std::shared_ptr<GraphicsInputLayout>& GetInputLayout() const noexcept { return m_InputLayout; }

		private:
			std::shared_ptr<GraphicsBuffer> m_VertexBuffer;
			std::shared_ptr<GraphicsBuffer> m_IndexBuffer;
			std::shared_ptr<GraphicsInputLayout> m_InputLayout;
	};

}
