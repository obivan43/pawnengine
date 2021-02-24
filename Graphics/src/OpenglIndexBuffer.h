#pragma once


#include "OpenglBufferBase.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglIndexBuffer : public OpenglBufferBase {

	public:
		OpenglIndexBuffer();
		OpenglIndexBuffer(const OpenglIndexBuffer& other) = default;
		OpenglIndexBuffer(OpenglIndexBuffer&& other) noexcept = default;

		OpenglIndexBuffer& operator=(const OpenglIndexBuffer& other) = default;
		OpenglIndexBuffer& operator=(OpenglIndexBuffer&& other) noexcept = default;
	};

}

#endif
