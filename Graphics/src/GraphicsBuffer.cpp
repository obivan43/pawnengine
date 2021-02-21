#include "pch.h"
#include "GraphicsBuffer.h"


namespace pawn {

	GraphicsBuffer::GraphicsBuffer()
	: m_GraphicsBufferType(GraphicsBufferEnum::None)
	{}

	void GraphicsBuffer::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
		(void)context;
		(void)data;
		(void)numVertices;
		(void)stride;
	}
	void GraphicsBuffer::Bind(std::shared_ptr<GraphicsContext>& context) { (void)context; }
}