#include "pch.h"
#include "MeshManager.h"

namespace pawn {

	bool MeshManager::UploadMesh(const std::string& name, const std::shared_ptr<Mesh>& mesh) {
		if (m_MeshesMap[name] != nullptr) {
			CONSOLE_WARN("MeshManager: mesh with same name already exist")
			return false;
		}

		m_MeshesMap[name] = mesh;

		return true;
	}

	bool MeshManager::UploadMeshFromFile(std::shared_ptr<pawn::GraphicsContext>& context, std::shared_ptr<pawn::GraphicsShader>& shader, const std::string& filename) {
		static const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float3 },
			{ "Normal", GraphicsInputElementType::Float3 },
			{ "TextureCoordinate", GraphicsInputElementType::Float2 }
		};

		std::string base_filename = filename.substr(filename.find_last_of("/\\") + 1);
		std::string::size_type const p(base_filename.find_last_of('.'));
		std::string file_without_extension = base_filename.substr(0, p);

		if (m_MeshesMap[file_without_extension] != nullptr) {
			CONSOLE_WARN("MeshManager: mesh with same name already exist")
			return false;
		}

		bool result = m_MeshLoader.LoadModel(filename.c_str());
		if (!result) {
			CONSOLE_WARN("MeshManager: mesh loading corrupted")
			return result;
		}

		std::vector<Vertex>& vertices = m_MeshLoader.GetVertexData();
		std::vector<uint16_t>& indices = m_MeshLoader.GetIndexData();

		std::shared_ptr<GraphicsBuffer> vertexBuffer = GraphicsBuffer::Create(GraphicsBufferEnum::VertexBuffer);
		std::shared_ptr<GraphicsBuffer> indexBuffer = GraphicsBuffer::Create(GraphicsBufferEnum::IndexBuffer);
		std::shared_ptr<GraphicsInputLayout> inputLayout = GraphicsInputLayout::Create();

		vertexBuffer->Init(context, vertices.data(), static_cast<uint32_t>(vertices.size()), sizeof(Vertex), GraphicsBufferUsageTypeEnum::StaticBuffer);
		vertexBuffer->Bind(context);

		indexBuffer->Init(context, indices.data(), static_cast<uint32_t>(indices.size()), sizeof(uint16_t), GraphicsBufferUsageTypeEnum::StaticBuffer);
		indexBuffer->Bind(context);

		inputLayout->Init(context, inputElements, shader->GetVertexShaderInfo());

		m_MeshesMap[file_without_extension].reset(new Mesh(vertexBuffer, indexBuffer, inputLayout));

		return true;
	}

	const std::shared_ptr<Mesh>& MeshManager::GetMeshByName(const std::string& name) {
		return m_MeshesMap[name];
	}

}