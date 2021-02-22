#include "pch.h"
#include "Opengl.h"
#include "OpenglVertexBuffer.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglVertexBuffer::OpenglVertexBuffer()
		: m_Buffer(0), m_BufferSize(0), m_Stride(0) {
		m_GraphicsBufferType = GraphicsBufferEnum::VertexBuffer;
	}

	OpenglVertexBuffer::~OpenglVertexBuffer() {
		glDeleteBuffers(1, &m_Buffer);
	}
	
	void OpenglVertexBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

	void OpenglVertexBuffer::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		UNUSED(context)
		
		m_BufferSize = numVertices;
		m_Stride = stride;

		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glBufferData(GL_ARRAY_BUFFER, numVertices * stride, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		spdlog::info("Vertex buffer created");
	}
	
}

#endif
