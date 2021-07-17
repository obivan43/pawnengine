#pragma once

#include "Mesh.h"

#include <string>

namespace pawn {

	namespace geometry {

		struct LODGroup {

			std::string name;
			std::vector<geometry::Mesh> meshes;

		};

	}

}
