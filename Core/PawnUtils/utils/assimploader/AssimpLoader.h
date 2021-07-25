#pragma once

#include "PawnMath/math/Vertex.h"

#include <string>
#include <vector>
#include <cstdint>

struct aiScene;
struct aiNode;
struct aiMesh;

namespace Assimp {
	class Importer;
}

namespace pawn {

	namespace utils {

		class AssimpLoader {

			public:
				AssimpLoader();
				AssimpLoader(const AssimpLoader& other) = delete;
				AssimpLoader(AssimpLoader&& other) noexcept = delete;

				AssimpLoader& operator=(const AssimpLoader& other) = delete;
				AssimpLoader& operator=(AssimpLoader&& other) noexcept = delete;

				~AssimpLoader();

				bool LoadModel(const char* file);
				void Flush();

				std::vector<math::Vertex>& GetVertexData() { return m_Verticies; }
				std::vector<uint16_t>& GetIndexData() { return m_Indices; }

			private:
				void ProcessData();
				void AssimpGetMeshData(const aiMesh* mesh);

			private:
				Assimp::Importer* m_Importer;

				const aiScene* m_ModelScene;
				const aiNode* m_ModelNode;

				std::vector<math::Vertex> m_Verticies;
				std::vector<uint16_t> m_Indices;
				std::vector<const aiNode*> m_Nodes;
		};

	}

}