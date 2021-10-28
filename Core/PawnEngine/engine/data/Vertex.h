#pragma once

#include "glm.hpp"

namespace pawn::engine {
	
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Binormal;
		glm::vec2 TextureCoordinate;
	};
	
}
