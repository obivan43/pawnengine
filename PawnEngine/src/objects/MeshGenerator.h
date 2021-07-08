#pragma once

#include "Scene.h"
#include "MeshInfo.h"

namespace geometry {

	class MeshGenerator {

		public:
			
			static void CreatePlane(Scene& scene, const MeshInfo& meshInfo);
			static void CreateCube(Scene& scene, const MeshInfo& meshInfo);
			static void CreateUVSphere(Scene& scene, const MeshInfo& meshInfo);
			static void CreateICOSphere(Scene& scene, const MeshInfo& meshInfo);
			static void CreateCylinder(Scene& scene, const MeshInfo& meshInfo);
			static void CreateCapsule(Scene& scene, const MeshInfo& meshInfo);

	};

}
