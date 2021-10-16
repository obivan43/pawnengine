#pragma once

#include "glm.hpp"

#include <cstdint>

namespace pawn::engine {

	struct MeshNodeData {
		uint32_t VertexShift;
		uint32_t IndexShift;
		uint32_t IndexCount;
		glm::mat4 Transformation;
		std::string Name;
	};

}
