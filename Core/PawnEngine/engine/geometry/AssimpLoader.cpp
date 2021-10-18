#include "AssimpLoader.h"

#include "MeshNodeData.h"

#include "PawnUtils/utils/logger/Logger.h"
#include "PawnGraphics/graphics/GraphicsShader.h"
#include "PawnGraphics/graphics/GraphicsShader.h"
#include "PawnGraphics/graphics/GraphicsBuffer.h"
#include "PawnGraphics/graphics/GraphicsInputLayout.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace pawn::engine {

	glm::mat4 convertAssimpTransformation(const aiMatrix4x4& matrix) {
		glm::mat4 result;

		result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
		result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
		result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
		result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;

		return result;
	}

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
		m_MeshNodeData.clear();
	}

	std::shared_ptr<Mesh> AssimpLoader::LoadModel(const char* file, std::shared_ptr<graphics::GraphicsContext>& context, std::shared_ptr<graphics::GraphicsShader>& shader) {
		Flush();

		m_ModelScene = m_Importer->ReadFile(file, 
			aiProcess_CalcTangentSpace	|
			aiProcess_Triangulate		|
			aiProcess_SortByPType		|
			aiProcess_GenNormals		|
			aiProcess_GenUVCoords		|
			aiProcess_OptimizeMeshes	|
			aiProcess_ValidateDataStructure
		);

		if (!m_ModelScene) {
			CONSOLE_INFO("Assimp loader: Model not loaded {}", file)
				return false;
		}

		return ProcessData(context, shader);
	}

	std::shared_ptr<Mesh> AssimpLoader::ProcessData(std::shared_ptr<graphics::GraphicsContext>& context, std::shared_ptr<graphics::GraphicsShader>& shader) {
		if (m_ModelScene->mNumMeshes > 0) {

			uint32_t vertexCount = 0;
			uint32_t indexCount = 0;
			m_MeshNodeData.reserve(m_ModelScene->mNumMeshes);

			for (uint32_t i = 0; i < m_ModelScene->mNumMeshes; ++i) {
				const aiMesh* mesh = m_ModelScene->mMeshes[i];

				MeshNodeData& meshNodeData = m_MeshNodeData.emplace_back();
				meshNodeData.VertexShift = vertexCount;
				meshNodeData.IndexShift = indexCount;
				meshNodeData.IndexCount = m_ModelScene->mMeshes[i]->mNumFaces * 3;
				meshNodeData.Name = mesh->mName.C_Str();

				vertexCount += mesh->mNumVertices;
				indexCount += meshNodeData.IndexCount;

				AssimpGetMeshData(mesh);
			}

			UpdateMeshDataInfo(m_ModelScene->mRootNode, glm::mat4(1.0));

			static const std::initializer_list<graphics::GraphicsInputElement> inputElements = {
				{ "Position", graphics::GraphicsInputElementType::Float3 },
				{ "Normal", graphics::GraphicsInputElementType::Float3 },
				{ "TextureCoordinate", graphics::GraphicsInputElementType::Float2 }
			};

			std::shared_ptr<graphics::GraphicsBuffer> vertexBuffer = graphics::GraphicsBuffer::Create(graphics::GraphicsBufferEnum::VertexBuffer);
			std::shared_ptr<graphics::GraphicsBuffer> indexBuffer = graphics::GraphicsBuffer::Create(graphics::GraphicsBufferEnum::IndexBuffer);
			std::shared_ptr<graphics::GraphicsInputLayout> inputLayout = graphics::GraphicsInputLayout::Create();

			vertexBuffer->Init(context, m_Verticies.data(), static_cast<uint32_t>(m_Verticies.size()), sizeof(Vertex), graphics::GraphicsBufferUsageTypeEnum::StaticBuffer);
			vertexBuffer->Bind(context);

			indexBuffer->Init(context, m_Indices.data(), static_cast<uint32_t>(m_Indices.size()), sizeof(uint32_t), graphics::GraphicsBufferUsageTypeEnum::StaticBuffer);
			indexBuffer->Bind(context);

			inputLayout->Init(context, inputElements, shader->GetVertexShaderInfo());
			inputLayout->Bind(context);

			Mesh* mesh = new Mesh();
			mesh->m_MeshNodeData = m_MeshNodeData;
			mesh->m_GraphicsMesh.reset(new graphics::GraphicsMesh(vertexBuffer, indexBuffer, inputLayout));

			return std::shared_ptr<Mesh>(mesh);
		}

		return std::shared_ptr<Mesh>();
	}

	void AssimpLoader::UpdateMeshDataInfo(const aiNode* node, const glm::mat4& transformation) {
		glm::mat4 resultTransformation = transformation * convertAssimpTransformation(node->mTransformation);

		for (uint32_t i = 0; i < node->mNumMeshes; i++) {
			uint32_t index = node->mMeshes[i];

			MeshNodeData& meshNodeData = m_MeshNodeData[index];
			meshNodeData.Name = node->mName.C_Str();
			meshNodeData.Transformation = resultTransformation;
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++) {
			UpdateMeshDataInfo(node->mChildren[i], resultTransformation);
		}
	}

	void AssimpLoader::AssimpGetMeshData(const aiMesh* mesh) {
		for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;

			if (mesh->HasTextureCoords(0)) {
				vertex.TextureCoordinate.x = mesh->mTextureCoords[0][i].x;
				vertex.TextureCoordinate.y = mesh->mTextureCoords[0][i].y;
			}
			else {
				vertex.TextureCoordinate.x = 0.0f;
				vertex.TextureCoordinate.y = 0.0f;
			}

			m_Verticies.push_back(vertex);
		}

		aiFace* face;
		for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
			face = &mesh->mFaces[i];

			if (face->mNumIndices < 3) {
				continue;
			}

			m_Indices.push_back(face->mIndices[0]);
			m_Indices.push_back(face->mIndices[1]);
			m_Indices.push_back(face->mIndices[2]);
		}
	}

}
