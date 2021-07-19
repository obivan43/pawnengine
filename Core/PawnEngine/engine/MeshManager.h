#pragma once

#include "PawnUtils/utils/assimploader/AssimpLoader.h"

#include "PawnGraphics/graphics/GraphicsContext.h"
#include "PawnGraphics/graphics/GraphicsShader.h"
#include "PawnGraphics/graphics/data/GraphicsMesh.h"

#include <memory>
#include <unordered_map>
#include <string>

namespace pawn {

	namespace engine {

		class MeshManager {

			public:
				MeshManager() = default;
				MeshManager(const MeshManager& other) = delete;
				MeshManager(MeshManager&& other) noexcept = delete;

				MeshManager& operator=(const MeshManager& other) = delete;
				MeshManager& operator=(MeshManager&& other) noexcept = delete;

				bool HasMeshByName(const std::string& name);
				bool UploadMesh(const std::string& name, const std::shared_ptr<graphics::GraphicsMesh>& mesh);

				bool UploadMeshFromFile(
					std::shared_ptr<graphics::GraphicsContext>& context,
					std::shared_ptr<graphics::GraphicsShader>& shader,
					const std::string& path
				);

				const std::shared_ptr<graphics::GraphicsMesh>& GetMeshByName(const std::string& name);

			private:
				std::unordered_map<std::string, std::shared_ptr<graphics::GraphicsMesh>> m_MeshesMap;
				utils::AssimpLoader m_MeshLoader;
		};

	}

}
