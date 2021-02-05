#include "pch.h"
#include "GraphicsBuffer.h"


namespace pawn {

	GraphicsBuffer::GraphicsBuffer()
	: m_graphicsBufferType(GraphicsBufferEnum::None)
	{}

	void GraphicsBuffer::Bind(std::shared_ptr<GraphicsContext>& context) { (void)context; }
}