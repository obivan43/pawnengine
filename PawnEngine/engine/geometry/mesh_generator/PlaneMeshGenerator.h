#pragma once

#include "MeshGenerator.h"

namespace pawn {

	namespace geometry {

		class PlaneMeshGenerator : public MeshGenerator {

			public:

				void CreateMesh(geometry::Scene& scene, const geometry::MeshInfo& meshInfo) override final;

				geometry::Mesh CreateMesh(
					const geometry::MeshInfo& meshInfo,
					uint32_t horizontalAxis = axis::x,
					uint32_t verticalAxis = axis::z,
					bool flipWinding = false,
					glm::vec3 offset = { -0.5, 0.0f, -0.5f },
					glm::vec2 urange = { 0.0f, 1.0f },
					glm::vec2 vrange = { 0.0f, 1.0f }
				);
		};

	}

}
