#pragma once

#include "glm.hpp"

namespace pawn {

	namespace geometry {

		enum class MeshType {
			Plane,
			Cube,
			UV_Sphere,
			ICO_Sphere,
			Cylinder,
			Capsule,

			Count
		};

		struct MeshInfo {

			MeshType type;
			glm::uvec3 segments{ 1, 1, 1 };
			glm::vec3 size{ 1, 1, 1 };
			uint32_t lod = 0;

		};

	}

}
