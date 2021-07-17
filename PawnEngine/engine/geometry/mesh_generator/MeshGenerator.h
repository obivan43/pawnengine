#pragma once

#include "PawnEngine/engine/geometry/Scene.h"
#include "PawnEngine/engine/geometry/MeshInfo.h"

namespace pawn {

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

}
