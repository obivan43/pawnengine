#pragma once

#include "OpenglBufferBase.h"

#ifdef PAWN_OPENGL

namespace pawn {
	
	class OpenglVertexBuffer : public OpenglBufferBase {

		public:
			OpenglVertexBuffer();
			OpenglVertexBuffer(const OpenglVertexBuffer& other) = default;
			OpenglVertexBuffer(OpenglVertexBuffer&& other) noexcept = default;

			OpenglVertexBuffer& operator=(const OpenglVertexBuffer& other) = default;
			OpenglVertexBuffer& operator=(OpenglVertexBuffer&& other) noexcept = default;
	};
	
}

#endif
