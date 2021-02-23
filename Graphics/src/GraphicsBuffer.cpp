#include "pch.h"
#include "GraphicsBuffer.h"
#include "GraphicsShader.h"


namespace pawn {

	GraphicsBuffer::GraphicsBuffer()
	: m_GraphicsBufferType(GraphicsBufferEnum::None)
	{}

	void GraphicsBuffer::InitLocation(
		std::shared_ptr<GraphicsContext>& context,
		std::shared_ptr<GraphicsShader>& shader, 
		const std::string& name,
		uint32_t index
	) {
		UNUSED(context)
		UNUSED(shader)
		UNUSED(name)
		UNUSED(index)
	}
	
	void GraphicsBuffer::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		UNUSED(context)
		UNUSED(data)
		UNUSED(numVertices)
		UNUSED(stride)
	}
	void GraphicsBuffer::Bind(std::shared_ptr<GraphicsContext>& context) { UNUSED(context) }
}