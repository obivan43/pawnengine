#include "PlaneMeshGenerator.h"

#include "PawnMath/math/Functions.h"

#include "PawnEngine/engine/geometry/LODGroup.h"

namespace geometry {

	void PlaneMeshGenerator::CreateMesh(geometry::Scene& scene, const geometry::MeshInfo& meshInfo) {
		geometry::LODGroup lod;
		lod.name = std::string("plane");
		lod.meshes.emplace_back(CreateMesh(meshInfo));

		scene.lodGroups.emplace_back(lod);
	}

	geometry::Mesh PlaneMeshGenerator::CreateMesh(
		const geometry::MeshInfo& meshInfo,
		uint32_t horizontalAxis,
		uint32_t verticalAxis,
		bool flipWinding,
		glm::vec3 offset, 
		glm::vec2 uRange,
		glm::vec2 vRange
	) {
		assert(horizontalAxis < axis::count && verticalAxis < axis::count);
		assert(horizontalAxis != verticalAxis);

		const uint32_t planeMinimum{ 1 };
		const uint32_t planeMaximum{ 256 };

		const uint32_t horizontalSize = math::clamp(meshInfo.segments[horizontalAxis], planeMinimum, planeMaximum);
		const uint32_t verticalSize = math::clamp(meshInfo.segments[verticalAxis], planeMinimum, planeMaximum);

		const float horizontalStep{ 1.0f / horizontalSize };
		const float verticalStep{ 1.0f / verticalSize };

		const float uStep{ (uRange.y - uRange.x) / horizontalSize };
		const float vStep{ (vRange.y - vRange.x) / verticalSize };

		geometry::Mesh plane;
		std::vector<glm::vec2> uvs;
		
		for (uint32_t i{ 0 }; i < verticalSize; ++i) {
			for (uint32_t j{ 0 }; j < horizontalSize; ++j) {
				glm::vec3 position{ offset };
				float* asArray{ &position.x };
				asArray[horizontalAxis] += j * horizontalStep;
				asArray[verticalAxis] += i * verticalStep;
				plane.positions.emplace_back(glm::vec3(position.x * meshInfo.size.x, position.y * meshInfo.size.y, position.z * meshInfo.size.z));

				glm::vec2 uv(uRange.x, 1.0f - vRange.x);
				uv.x += j * uStep;
				uv.y -= i * vStep;
				uvs.emplace_back(uv);
			}
		}

		const uint32_t rowLength = horizontalSize + 1;
		for (uint32_t i{ 0 }; i < verticalSize; ++i) {
			for (uint32_t j{ 0 }; j < horizontalSize; ++j) {
				const uint32_t index[4]
				{
					j + i * rowLength,
					j + (i + 1) * rowLength,
					(j + 1) + i  * rowLength,
					(j + 1) + (i + 1) * rowLength
				};

				plane.indicies.emplace_back(index[0]);
				plane.indicies.emplace_back(index[flipWinding ? 2 : 1]);
				plane.indicies.emplace_back(index[flipWinding ? 2 : 1]);

				plane.indicies.emplace_back(index[2]);
				plane.indicies.emplace_back(index[flipWinding ? 3 : 1]);
				plane.indicies.emplace_back(index[flipWinding ? 1 : 3]);
			}
		}

		const uint32_t indiciesSize{ 6 * horizontalSize * verticalSize };
		assert(plane.indicies.size() == indiciesSize);

		for (uint32_t i{ 0 }; i < indiciesSize; ++i) {
			plane.uvcoordinates[0].emplace_back(uvs[plane.indicies[i]]);
		}

		return plane;
	}

}
