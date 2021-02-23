#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglConstantBuffer.h"

#include "GraphicsShader.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglConstantBuffer::OpenglConstantBuffer()
		: m_BufferSize(0), m_Stride(0), m_UniformIndex(0) {
		m_GraphicsBufferType = GraphicsBufferEnum::ConstantBuffer;
	}

	OpenglConstantBuffer::~OpenglConstantBuffer() {
		OpenglCall(glDeleteBuffers(1, &m_Buffer))
	}

	void OpenglConstantBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
		OpenglCall(glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer))
		OpenglCall(glBindBufferBase(GL_UNIFORM_BUFFER, m_BindingIndex, m_Buffer))
	}

	void OpenglConstantBuffer::InitLocation(
		std::shared_ptr<GraphicsContext>& context,
		std::shared_ptr<GraphicsShader>& shader,
		const std::string& name,
		uint32_t index
	) {
		UNUSED(context)
		m_BindingIndex = index;
		OpenglCall(m_UniformIndex = glGetUniformBlockIndex(reinterpret_cast<uint32_t>(shader->GetShader()), name.c_str()))
		OpenglCall(glUniformBlockBinding(reinterpret_cast<uint32_t>(shader->GetShader()), m_UniformIndex, m_BindingIndex))
	}
	
	void OpenglConstantBuffer::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		UNUSED(context)

		m_BufferSize = numVertices;
		m_Stride = stride;
		
		OpenglCall(glGenBuffers(1, &m_Buffer))
		OpenglCall(glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer))
		OpenglCall(glBufferData(GL_UNIFORM_BUFFER, numVertices * stride, data, GL_DYNAMIC_DRAW))
		OpenglCall(glBindBuffer(GL_UNIFORM_BUFFER, 0))
		
		spdlog::get("console")->info("Constant buffer created");
	}
}

#endif
