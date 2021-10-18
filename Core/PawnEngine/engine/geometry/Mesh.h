#pragma once

#include "PawnGraphics/graphics/data/GraphicsMesh.h"

#include "MeshNodeData.h"

namespace pawn::engine {

	class AssimpLoader;

	class Mesh {

		friend AssimpLoader;

		public:

			Mesh() = default;
			Mesh(const Mesh & other) = default;
			Mesh(Mesh && other) noexcept = default;

			Mesh& operator=(const Mesh & other) = default;
			Mesh& operator=(Mesh && other) noexcept = default;

			const std::vector<MeshNodeData>& GetMeshNodeData() { return m_MeshNodeData; }
			std::shared_ptr<graphics::GraphicsMesh> GetGraphicsMesh() { return m_GraphicsMesh; }

		private:
			std::vector<MeshNodeData> m_MeshNodeData;
			std::shared_ptr<graphics::GraphicsMesh> m_GraphicsMesh;
	};

}
