#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglBufferBase.h"

#ifdef PAWN_OPENGL

namespace pawn {

	uint32_t OpenglBufferBase::BufferTypeToOpenglBufferType(GraphicsBufferEnum type) {
		switch(type) {
			case GraphicsBufferEnum::VertexBuffer:
				return GL_ARRAY_BUFFER;
			case GraphicsBufferEnum::IndexBuffer:
				return GL_ELEMENT_ARRAY_BUFFER;
			case GraphicsBufferEnum::ConstantBuffer:
				return GL_UNIFORM_BUFFER;
		}

		return GL_INVALID_ENUM;
	}

	const char* OpenglBufferBase::BufferTypeMessage(GraphicsBufferEnum type) {
		switch (type) {
			case GraphicsBufferEnum::VertexBuffer:
				return "Vertex";
			case GraphicsBufferEnum::IndexBuffer:
				return "Index";
			case GraphicsBufferEnum::ConstantBuffer:
				return "Uniform";
		}

		return "";
	}
	
	uint32_t OpenglBufferBase::BufferUsageTypeToOpenglBufferUsageType(GraphicsBufferUsageTypeEnum usageType) {
		switch (usageType) {
			case GraphicsBufferUsageTypeEnum::StaticBuffer:
				return GL_STATIC_DRAW;
			case GraphicsBufferUsageTypeEnum::DynamicBuffer:
				return GL_DYNAMIC_DRAW;
		}

		return GL_INVALID_ENUM;
	}

	OpenglBufferBase::OpenglBufferBase(GraphicsBufferEnum type)
		: m_Buffer(0), m_BufferSize(0), m_Stride(0), m_UsageType(GraphicsBufferUsageTypeEnum::None) {
		m_GraphicsBufferType = type;
	}

	OpenglBufferBase::~OpenglBufferBase() {
		OpenglCall(glDeleteBuffers(1, &m_Buffer))
	}

	void OpenglBufferBase::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
		OpenglCall(glBindBuffer(BufferTypeToOpenglBufferType(m_GraphicsBufferType), m_Buffer))
	}

	void OpenglBufferBase::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}

	void OpenglBufferBase::Update(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		const uint32_t bufferType = BufferTypeToOpenglBufferType(m_GraphicsBufferType);
		switch (m_UsageType) {
			case GraphicsBufferUsageTypeEnum::StaticBuffer: {
				Init(context, data, numVertices, stride, m_UsageType);
			}
			break;

			case GraphicsBufferUsageTypeEnum::DynamicBuffer: {
				void* bufferData = nullptr;
				OpenglCall(glBindBuffer(bufferType, m_Buffer))
				OpenglCall(bufferData = glMapBuffer(bufferType, GL_WRITE_ONLY))
				memcpy(bufferData, data, numVertices * stride);
				OpenglCall(glUnmapBuffer(bufferType))
				OpenglCall(glBindBuffer(bufferType, 0))
			}
			break;

			default: break;
		}
	}

	void OpenglBufferBase::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride, GraphicsBufferUsageTypeEnum type) {
		UNUSED(context)

		if (m_Buffer != 0) {
			OpenglCall(glDeleteBuffers(1, &m_Buffer))
			m_Buffer = 0;
		}

		m_BufferSize = numVertices;
		m_Stride = stride;
		m_UsageType = type;

		const uint32_t bufferType = BufferTypeToOpenglBufferType(m_GraphicsBufferType);
		OpenglCall(glGenBuffers(1, &m_Buffer))
		OpenglCall(glBindBuffer(bufferType, m_Buffer))
		OpenglCall(glBufferData(bufferType, numVertices * stride, data, BufferUsageTypeToOpenglBufferUsageType(type)))
		OpenglCall(glBindBuffer(bufferType, 0))

		spdlog::get("console")->info("{} buffer created", BufferTypeMessage(m_GraphicsBufferType));
	}

}

#endif
