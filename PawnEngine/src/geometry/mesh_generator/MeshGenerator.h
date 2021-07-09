#pragma once

#include "../Scene.h"
#include "../MeshInfo.h"

namespace geometry {

	namespace axis {

		enum Axis {
			x,
			y,
			z,
			count
		};

	}

	class MeshGenerator {

		public:
			
			virtual ~MeshGenerator();

			virtual void CreateMesh(geometry::Scene& scene, const geometry::MeshInfo& meshInfo) = 0;

	};

}
