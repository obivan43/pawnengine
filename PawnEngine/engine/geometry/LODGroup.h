#pragma once

#include "Mesh.h"

#include <string>

namespace geometry {

	struct LODGroup {

		std::string name;
		std::vector<geometry::Mesh> meshes;

	};

}