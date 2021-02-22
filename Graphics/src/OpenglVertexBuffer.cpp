#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglVertexBuffer.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglVertexBuffer::OpenglVertexBuffer()
		: m_Buffer(0), m_BufferSize(0), m_Stride(0) {
		m_GraphicsBufferType = GraphicsBufferEnum::VertexBuffer;
	}

	OpenglVertexBuffer::~OpenglVertexBuffer() {
		OpenglCall(glDeleteBuffers(1, &m_Buffer))
	}
	
	void OpenglVertexBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
		OpenglCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer))
	}

	void OpenglVertexBuffer::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		UNUSED(context)
		
		m_BufferSize = numVertices;
		m_Stride = stride;

		OpenglCall(glGenBuffers(1, &m_Buffer))
		OpenglCall(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer))
		OpenglCall(glBufferData(GL_ARRAY_BUFFER, numVertices * stride, data, GL_STATIC_DRAW))
		OpenglCall(glBindBuffer(GL_ARRAY_BUFFER, 0))

		spdlog::get("console")->info("Vertex buffer created");
	}
	
}

#endif
