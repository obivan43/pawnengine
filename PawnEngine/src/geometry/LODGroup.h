#pragma once

#include "Mesh.h"

namespace geometry {

	struct LODGroup {

		std::string name;
		std::vector<geometry::Mesh> meshes;

	};

}