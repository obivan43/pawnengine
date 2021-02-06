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

			virtual uint32_t GetBufferSize() const = 0;
			virtual uint32_t GetStride() const = 0;
		
			const GraphicsBufferEnum& GetGraphicsBufferType() const { return m_graphicsBufferType; }

		protected:
			GraphicsBufferEnum m_graphicsBufferType;
	};
	
}
