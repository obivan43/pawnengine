#pragma once

namespace pawn {

	class GraphicsContext;

	enum class GraphicsBufferEnum {
		None,
		VertexBuffer,
		IndexBuffer,
		ConstantBuffer,
		Count
	};
	
	class GraphicsBuffer {

		public:
			GraphicsBuffer();
			GraphicsBuffer(const GraphicsBuffer& other) = default;
			GraphicsBuffer(GraphicsBuffer&& other) noexcept = default;

			GraphicsBuffer& operator=(const GraphicsBuffer& other) = default;
			GraphicsBuffer& operator=(GraphicsBuffer&& other) noexcept = default;

			virtual ~GraphicsBuffer() = default;

			virtual void Bind(std::shared_ptr<GraphicsContext>& context);
		
			const GraphicsBufferEnum& GetGraphicsBufferType() const { return m_graphicsBufferType; }

		protected:
			GraphicsBufferEnum m_graphicsBufferType;
	};
	
}
