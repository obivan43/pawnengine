#pragma once

#include "GraphicsBuffer.h"

#ifdef PAWN_OPENGL

namespace pawn {
	
	class OpenglVertexBuffer : public GraphicsBuffer {

		public:
			OpenglVertexBuffer();
			OpenglVertexBuffer(const OpenglVertexBuffer& other) = default;
			OpenglVertexBuffer(OpenglVertexBuffer&& other) noexcept = default;

			OpenglVertexBuffer& operator=(const OpenglVertexBuffer& other) = default;
			OpenglVertexBuffer& operator=(OpenglVertexBuffer&& other) noexcept = default;

			~OpenglVertexBuffer()
				;
			void Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t sizeofBufferDataType) override;
			void Bind(std::shared_ptr<GraphicsContext>& context) override;

			void* GetBuffer() const override { return reinterpret_cast<void*>(m_Buffer); }
			uint32_t GetBufferSize() const override { return m_BufferSize; }
			uint32_t GetStride() const override { return m_Stride; }

		private:
			uint32_t m_Buffer;
			uint32_t m_BufferSize;
			uint32_t m_Stride;
	};
	
}

#endif
