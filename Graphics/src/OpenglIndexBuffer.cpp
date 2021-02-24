#include "pch.h"
#include "OpenglIndexBuffer.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglIndexBuffer::OpenglIndexBuffer() : OpenglBufferBase(GraphicsBufferEnum::IndexBuffer) {}

}

#endif