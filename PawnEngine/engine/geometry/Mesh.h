#pragma once

#include "glm.hpp"

#include <vector>

namespace geometry {

	struct Mesh {

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> noramls;
		std::vector<glm::vec3> tangents;
		std::vector<std::vector<glm::vec2>> uvcoordinates;
		std::vector<uint16_t> indicies;

	};

}
