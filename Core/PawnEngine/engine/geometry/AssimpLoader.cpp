#include "AssimpLoader.h"

#include "PawnUtils/utils/logger/Logger.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace pawn::engine {

	AssimpLoader::AssimpLoader() {
		m_Importer = new Assimp::Importer();
		m_ModelScene = nullptr;
		m_ModelNode = nullptr;
	}

	AssimpLoader::~AssimpLoader() {
		Flush();
		delete m_Importer;
	}

	void AssimpLoader::Flush() {
		m_ModelScene = nullptr;
		m_ModelNode = nullptr;
		m_Verticies.clear();
		m_Indices.clear();
		m_Nodes.clear();
	}

	bool AssimpLoader::LoadModel(const char* file) {
		Flush();

		m_ModelScene = m_Importer->ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

		if (!m_ModelScene) {
			CONSOLE_INFO("Assimp loader: Model not loaded {}", file)
				return false;
		}

		ProcessData();
		CONSOLE_INFO("Assimp loader: Model loaded {}", file)

			return true;
	}

	void AssimpLoader::ProcessData() {
		bool repeat = true;

		m_Nodes.push_back(m_ModelScene->mRootNode);

		while (repeat) {
			for (size_t i = 0; i < m_Nodes.size(); i++) {
				m_ModelNode = m_Nodes.at(i);
				if (m_ModelNode->mNumChildren > 0) {
					for (uint32_t j = 0; j < m_ModelNode->mNumChildren; j++) {
						m_Nodes.push_back(m_ModelNode->mChildren[j]);
					}
				}
				else {
					repeat = false;
				}
			}
		}

		for (size_t i = 0; i < m_Nodes.size(); i++) {
			m_ModelNode = m_Nodes.at(i);

			if (m_ModelNode->mNumMeshes > 0) {
				for (uint32_t j = 0; j < m_ModelNode->mNumMeshes; j++) {
					AssimpGetMeshData(m_ModelScene->mMeshes[j]);
				}
			}
		}

	}

	void AssimpLoader::AssimpGetMeshData(const aiMesh* mesh) {
		aiFace* face;

		m_Verticies.reserve(mesh->mNumVertices);
		for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;

			if (mesh->HasTextureCoords(0)) {
				vertex.TextureCoordinate.u = mesh->mTextureCoords[0][i].x;
				vertex.TextureCoordinate.v = mesh->mTextureCoords[0][i].y;
			}
			else {
				vertex.TextureCoordinate.u = 0.0f;
				vertex.TextureCoordinate.v = 0.0f;
			}

			m_Verticies.push_back(vertex);
		}

		for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
			face = &mesh->mFaces[i];
			m_Indices.push_back(face->mIndices[0]);
			m_Indices.push_back(face->mIndices[1]);
			m_Indices.push_back(face->mIndices[2]);
		}
	}

}
