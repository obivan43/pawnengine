#pragma once

#include "LODGroup.h"

namespace pawn {

	namespace geometry {

		struct Scene {

			std::string name;
			std::vector<LODGroup> lodGroups;

		};

		struct ImportSettings {

			float smoothingAngle;
			bool calculateNormals;
			bool calculateTangent;
			bool reverseHanded;
			bool importTextures;
			bool importAnimation;

		};

		struct SceneData {

			uint8_t* buffer;
			uint32_t bufferSize;
			ImportSettings settings;

		};

	}

}
