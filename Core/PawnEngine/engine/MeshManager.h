#pragma once

#include "PawnEngine/engine/data/AssimpLoader.h"
#include "PawnEngine/engine/data/Mesh.h"
#include "PawnGraphics/graphics/GraphicsContext.h"
#include "PawnGraphics/graphics/data/GraphicsMesh.h"
#include "PawnGraphics/graphics/GraphicsShader.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace pawn::engine {

	class MeshManager {

		public:
			MeshManager() = default;
			MeshManager(const MeshManager& other) = delete;
			MeshManager(MeshManager&& other) noexcept = delete;

			MeshManager& operator=(const MeshManager& other) = delete;
			MeshManager& operator=(MeshManager&& other) noexcept = delete;

			bool HasMeshByName(const std::string& name);
			bool UploadMesh(const std::string& name, const std::shared_ptr<Mesh>& mesh);

			bool UploadMeshFromFile(
				std::shared_ptr<graphics::GraphicsContext>& context,
				std::shared_ptr<graphics::GraphicsShader>& shader,
				const std::string& path
			);

			const std::shared_ptr<Mesh>& GetMeshByName(const std::string& name);

		private:
			std::unordered_map<std::string, std::shared_ptr<Mesh>> m_MeshesMap;
			AssimpLoader m_MeshLoader;
	};

}
