#pragma once

#include "GraphicsBindableResource.h"

namespace pawn {

	class GraphicsContext;

	enum class GraphicsBufferEnum {
		None,
		VertexBuffer,
		IndexBuffer,
		ConstantBuffer,
		Count
	};
	
	class GraphicsBuffer : public GraphicsBindableResource {

		public:
			GraphicsBuffer();
			GraphicsBuffer(const GraphicsBuffer& other) = default;
			GraphicsBuffer(GraphicsBuffer&& other) noexcept = default;

			GraphicsBuffer& operator=(const GraphicsBuffer& other) = default;
			GraphicsBuffer& operator=(GraphicsBuffer&& other) noexcept = default;

			virtual ~GraphicsBuffer() = default;

			void Bind(std::shared_ptr<GraphicsContext>& context) override;
		
			virtual uint32_t GetBufferSize() const = 0;
			virtual uint32_t GetStride() const = 0;
		
			const GraphicsBufferEnum& GetGraphicsBufferType() const { return m_graphicsBufferType; }

		protected:
			GraphicsBufferEnum m_graphicsBufferType;
	};
	
}
