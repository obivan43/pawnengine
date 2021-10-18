#pragma once

#include "Vertex.h"
#include "Mesh.h"
#include "MeshNodeData.h"

#include <string>
#include <vector>
#include <cstdint>

struct aiScene;
struct aiNode;
struct aiMesh;

namespace Assimp {
	class Importer;
}

namespace pawn::engine {

	class AssimpLoader {

		public:
			AssimpLoader();
			AssimpLoader(const AssimpLoader& other) = delete;
			AssimpLoader(AssimpLoader&& other) noexcept = delete;

			AssimpLoader& operator=(const AssimpLoader& other) = delete;
			AssimpLoader& operator=(AssimpLoader&& other) noexcept = delete;

			~AssimpLoader();

			std::shared_ptr<Mesh> LoadModel(const char* file, std::shared_ptr<graphics::GraphicsContext>& context, std::shared_ptr<graphics::GraphicsShader>& shader);
			void Flush();

		private:
			std::shared_ptr<Mesh> ProcessData(std::shared_ptr<graphics::GraphicsContext>& context, std::shared_ptr<graphics::GraphicsShader>& shader);
			void AssimpGetMeshData(const aiMesh* mesh);
			void UpdateMeshDataInfo(const aiNode* node, const glm::mat4& transformation);

		private:
			Assimp::Importer* m_Importer;

			const aiScene* m_ModelScene;
			const aiNode* m_ModelNode;

			std::vector<MeshNodeData> m_MeshNodeData;
			std::vector<Vertex> m_Verticies;
			std::vector<uint32_t> m_Indices;
			std::vector<const aiNode*> m_Nodes;
	};
}
