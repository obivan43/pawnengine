#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglConstantBuffer.h"

#include "GraphicsShader.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglConstantBuffer::OpenglConstantBuffer() : OpenglBufferBase(GraphicsBufferEnum::ConstantBuffer), m_UniformIndex(0), m_BindingIndex(0) {}

	void OpenglConstantBuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		OpenglBufferBase::Bind(context);
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

		const uint32_t shaderID = FROM_VOIDP(uint32_t, shader->GetShader());;
		OpenglCall(m_UniformIndex = glGetUniformBlockIndex(shaderID, name.c_str()))
		OpenglCall(glUniformBlockBinding(shaderID, m_UniformIndex, m_BindingIndex))
	}

	void OpenglConstantBuffer::Init(
		std::shared_ptr<GraphicsContext>& context,
		void* data,
		uint32_t numVertices,
		uint32_t sizeofBufferDataType,
		GraphicsBufferUsageTypeEnum type
	) {
		OpenglBufferBase::Init(context, data, numVertices, sizeofBufferDataType, type);
	}
}

#endif
