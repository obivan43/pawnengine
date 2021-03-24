#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace pawn {

	class Mesh;

	class MeshManager {

		public:
			MeshManager() = default;
			MeshManager(const MeshManager& other) = delete;
			MeshManager(MeshManager&& other) noexcept = delete;

			MeshManager& operator=(const MeshManager& other) = delete;
			MeshManager& operator=(MeshManager&& other) noexcept = delete;

			bool UploadMesh(const std::string& name, const std::shared_ptr<Mesh>& mesh);

			bool UploadMeshFromFile(
				std::shared_ptr<pawn::GraphicsContext>& context,
				std::shared_ptr<pawn::GraphicsShader>& shader,
				const std::string& filename
			);

			const std::shared_ptr<Mesh>& GetMeshByPath(const std::string& path);

		private:
			std::unordered_map<std::string, std::shared_ptr<Mesh>> m_MeshesMap;
			AssimpLoader m_MeshLoader;
	};

}